#include <sys/errno.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "mini_lib.h"

#define IOBUFFER_SIZE 2048 // Defines the buffer size for I/O operations

struct MYFILE {
  int fd;
  void *buffer_read;
  void *buffer_write;
  int ind_read;
  int ind_write;
};

// Node structure for a linked list of MYFILE objects
typedef struct MYFILE_NODE {
  MYFILE *file;
  struct MYFILE_NODE *next;
} MYFILE_NODE;

// Global list of open MYFILE objects
MYFILE_NODE *myFileList = NULL;

/*
 * add_file_to_list - Adds a MYFILE object to the global list of open files.
 *
 * @file: Pointer to the MYFILE object to add.
 *
 * Adds a new node containing the MYFILE object to the global list `myFileList`.
 *
 * Returns: 42 on success, 0 on failure.
 */
int add_file_to_list(MYFILE *file) {
  MYFILE_NODE *new_node = (MYFILE_NODE *)mini_calloc(sizeof(MYFILE_NODE), 1);
  if (new_node == NULL) {
    return 0;
  }

  new_node->file = file;
  new_node->next = myFileList;
  myFileList = new_node;

  return 42;
}

/*
 * del_file_from_list - Removes a MYFILE from the global list of open files.
 *
 * @file: Pointer to the MYFILE object to be removed.
 *
 * This function traverses the global list of open files and removes the node
 * containing the specified MYFILE object. If the file is not found, an error is
 * returned.
 *
 * Returns: 42 if successful, -1 if an error occurs (e.g., if the file does not
 * exist).
 */
int del_file_from_list(MYFILE *file) {
  if (file == NULL || myFileList == NULL) {
    errno = EINVAL;
    return -1;
  }

  MYFILE_NODE *current = myFileList;
  MYFILE_NODE *previous = NULL;

  while (current != NULL) {
    if (current->file == file) {
      if (previous == NULL) {
        myFileList = current->next;
      } else {
        previous->next = current->next;
      }

      mini_free(current);
      return 42;
    }

    previous = current;
    current = current->next;
  }

  errno = ENOENT;
  return -1;
}

MYFILE *mini_fopen(char *file, char mode) {
  MYFILE *myFile = (MYFILE *)mini_calloc(sizeof(MYFILE), 1);

  if (myFile == NULL) {
    return NULL;
  }

  int failed = add_file_to_list(myFile);

  if (failed == 0) {
    mini_free(myFile);
    errno = EIO;
    return NULL;
  }

  myFile->buffer_read = NULL;
  myFile->buffer_write = NULL;
  myFile->ind_read = -1;
  myFile->ind_write = -1;

  int flags;
  switch (mode) {
  case 'r':
    flags = O_RDONLY;
    break;
  case 'w':
    flags = O_WRONLY | O_CREAT | O_TRUNC;
    break;
  case 'b':
    flags = O_RDWR | O_CREAT;
    break;
  case 'a':
    flags = O_WRONLY | O_CREAT | O_APPEND;
    break;
  default:
    mini_free(myFile);
    errno = EINVAL;
    return NULL;
  }

  myFile->fd = open(file, flags, 0664);
  // 0664 is the permission descriptor in case of a newly created
  // 6 for owner (read + write)
  // 6 for groupe (read + write)
  // 4 for others (read)
  if (myFile->fd == -1) {
    mini_free(myFile);
    return NULL;
  }

  return myFile;
}

/*
 * init_buffer - Initializes a buffer and index for read or write operations.
 *
 * @buffer: Pointer to the buffer to be initialized.
 * @index: Pointer to the index to be initialized.
 *
 * This function allocates memory for a buffer if it has not been allocated
 * already and sets the provided index to 0.
 *
 * Returns: 0 if successful, -1 if memory allocation fails.
 */
int init_buffer(void **buffer, int *index) {
  if (*buffer == NULL) {
    *buffer = mini_calloc(1, IOBUFFER_SIZE);
    if (*buffer == NULL) {
      return -1;
    }
    *index = 0;
  }
  return 0;
}

int mini_fread(void *buffer, int size_element, int number_element,
               MYFILE *file) {
  if (file == NULL || file->fd < 0 || buffer == NULL || size_element <= 0 ||
      number_element <= 0) {
    errno = EINVAL;
    return -1;
  }

  if (init_buffer(&(file->buffer_read), &(file->ind_read)) == -1) {
    return -1;
  }

  int bToRead = size_element * number_element;
  int bRead = 0;
  char *src = (char *)file->buffer_read;
  char *dest = (char *)buffer;

  while (bRead < bToRead) {
    if (file->ind_read >= IOBUFFER_SIZE || file->ind_read == 0) {
      int read_result = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
      if (read_result < 0) {
        return -1;
      } else if (read_result == 0) { // Special case where read attains EOF
        break;
      }

      file->ind_read = 0;
    }

    if (file->ind_read < IOBUFFER_SIZE) {
      *dest = src[file->ind_read];

      dest++;
      file->ind_read++;
      bRead++;
    }
  }

  return bRead / size_element;
}

int mini_fwrite(void *buffer, int size_element, int number_element,
                MYFILE *file) {
  if (file == NULL || file->fd < 0 || buffer == NULL || size_element <= 0 ||
      number_element <= 0) {
    errno = EINVAL;
    return -1;
  }

  if (init_buffer(&(file->buffer_write), &(file->ind_write)) == -1) {
    return -1;
  }

  int bToWrite = size_element * number_element;
  int bWritten = 0;
  char *src = (char *)buffer;
  char *dest = (char *)file->buffer_write;

  while (bWritten < bToWrite) {
    dest[file->ind_write] = *src;

    src++;
    file->ind_write++;
    bWritten++;

    if (file->ind_write >= IOBUFFER_SIZE) {
      int write_result = write(file->fd, file->buffer_write, IOBUFFER_SIZE);
      if (write_result < 0) {
        return -1;
      }

      file->ind_write = 0;
    }
  }

  return bWritten / size_element;
}

int mini_fflush(MYFILE *file) {
  if (file == NULL) {
    errno = EINVAL;
    return -1;
  }

  int write_result = 0;

  if (file->buffer_write != NULL) {
    write_result = write(file->fd, file->buffer_write, file->ind_write);
    if (write_result == -1) {
      return -1;
    }
    file->ind_write = 0;
  }

  return write_result;
}

int mini_fclose(MYFILE *file) {
  if (file == NULL || myFileList == NULL) {
    errno = EINVAL;
    return -1;
  }

  int del_result = del_file_from_list(file);
  if (del_result == -1) {
    return -1;
  }

  int mini_fflush_result = mini_fflush(file);
  if (mini_fflush_result == -1) {
    return -1;
  }

  int close_result = close(file->fd);
  if (close_result == -1) {
    return -1;
  }

  mini_free(file);

  return 42;
}

int mini_fgetc(MYFILE *file) {
  if (file == NULL || file->fd < 0) {
    errno = EINVAL;
    return -1;
  }

  if (init_buffer(&(file->buffer_read), &(file->ind_read)) == -1) {
    return -1;
  }

  if (file->ind_read >= IOBUFFER_SIZE || file->ind_read == 0) {
    int read_result = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
    if (read_result < 0) {
      return -1;
    } else if (read_result == 0) {
      return -1;
    }

    file->ind_read = 0;
  }

  unsigned char character =
      ((unsigned char *)file->buffer_read)[file->ind_read];
  file->ind_read++;

  return character;
}

int mini_fputc(MYFILE *file, char c) {
  if (file == NULL || file->fd < 0) {
    errno = EINVAL;
    return -1;
  }

  if (init_buffer(&(file->buffer_write), &(file->ind_write)) == -1) {
    return -1;
  }

  ((char *)file->buffer_write)[file->ind_write] = c;
  file->ind_write++;

  if (file->ind_write >= IOBUFFER_SIZE) {
    int write_result = write(file->fd, file->buffer_write, IOBUFFER_SIZE);
    if (write_result < 0) {
      return -1;
    }

    file->ind_write = 0;
  }

  return (unsigned char)c;
}

void mini_io_exit(void) {
  MYFILE_NODE *current = myFileList;
  while (current != NULL) {
    MYFILE *file = current->file;
    if (file != NULL && file->buffer_write != NULL && file->ind_write > 0) {
      mini_fclose(file);
    }

    MYFILE_NODE *to_free = current;
    current = current->next;
    mini_free(to_free->file);
    mini_free(to_free);
  }
}

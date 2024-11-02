#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "mini_lib.h"

#define IOBUFFER_SIZE 2048

struct MYFILE {
  int fd;
  void *buffer_read;
  void *buffer_write;
  int ind_read;
  int ind_write;
};

MYFILE *mini_fopen(char *file, char mode) {
  MYFILE *myFile = (MYFILE *)mini_calloc(sizeof(MYFILE), 1);

  if (myFile == NULL) {
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
    errno = EINVAL; // Set errno to invalid args
    return NULL;
  }

  myFile->fd = open(file, flags);
  if (myFile->fd == -1) {
    mini_free(myFile);
    return NULL;
  }

  return myFile;
}

int mini_fread(void *buffer, int size_element, int number_element,
               MYFILE *file) {
  if (file == NULL || file->fd < 0 || buffer == NULL || size_element <= 0 ||
      number_element <= 0) {
    errno = EINVAL;
    return -1;
  }

  if (file->buffer_read == NULL) {
    file->buffer_read = mini_calloc(1, IOBUFFER_SIZE);
    if (file->buffer_read == NULL) {
      return -1;
    }
    file->ind_read = 0;
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
      } else if (read_result == 0) {
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

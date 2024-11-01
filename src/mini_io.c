#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "mini_lib.h"

#define IOBUFFER_SIZE 2048

typedef struct MYFILE {
  int fd;
  void *buffer_read;
  void *buffer_write;
  int ind_read;
  int ind_write;
} MYFILE;

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

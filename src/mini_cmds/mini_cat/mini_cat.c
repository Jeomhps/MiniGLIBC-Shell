#include <stdio.h>

#include "../../mini_glibc/mini_lib.h"

#define BUF_SIZE 2048

int main(int argc, char *argv[]) {

  if (argc != 2) {
    mini_printf("Usage: cat <filename>\n");
    mini_exit(1);
  }

  char *filename = argv[1];
  MYFILE *file = mini_fopen(filename, 'r');
  if (file == NULL) {
    mini_perror("Error opening the file");
    mini_exit(1);
  }

  char buffer[BUF_SIZE];

  int bRead;
  while ((bRead = mini_fread(buffer, sizeof(char), 1024, file)) > 0) {
    buffer[bRead] = '\0';
    mini_printf(buffer);
  }

  if (mini_fclose(file) == -1) {
    mini_perror("Error closing the file");
    mini_exit(1);
  }

  mini_exit(0);
}

#include "../../mini_glibc/mini_lib.h"

#define BUF_SIZE 8192

int main(int argc, char *argv[]) {

  if (argc != 2) {
    mini_printf("Usage: cat <filename>\n");
    return 1;
  }

  char *filename = argv[1];
  char buffer[BUF_SIZE];
  MYFILE *file = mini_fopen(filename, 'r');
  if (file == NULL) {
    mini_perror("Error opening the file");
    return 1;
  }

  int bytes_read;
  while ((bytes_read = mini_fread(buffer, sizeof(char), BUF_SIZE, file)) > 0) {
    buffer[bytes_read] = '\0';
    mini_printf(buffer);
  }

  if (mini_fclose(file) == -1) {
    mini_perror("Error closing the file");
    return 1;
  }

  return 0;
}

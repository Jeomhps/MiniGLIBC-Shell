#include "../../mini_glibc/mini_lib.h"
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc != 4) {
    mini_printf("Usage: -n N filename\n");
    return 1;
  }

  if (mini_strcmp(argv[1], "-n") != 0) {
    mini_printf("Usage: -n N filename\n");
    return 1;
  }

  int n = atoi(argv[2]);
  if (n <= 0) {
    mini_perror("Error: N must be a positive integer.");
    return 1;
  }

  MYFILE *file = mini_fopen(argv[3], 'r');
  if (file == NULL) {
    mini_perror("Error opening file");
    return 1;
  }

  char buffer[BUF_SIZE];
  int index = 0;
  int c;
  int line_count = 0;

  while ((c = mini_fgetc(file)) != -1) {
    buffer[index] = (char)c;
    index++;

    if (c == '\n' || index >= BUF_SIZE - 1) {
      buffer[index] = '\0';
      mini_printf(buffer);
      index = 0;

      if (c == '\n') {
        line_count++;
        if (line_count >= n) {
          break;
        }
      }
    }
  }

  if (index > 0) {
    buffer[index] = '\0';
    mini_printf(buffer);
  }

  mini_fclose(file);
  return 0;
}

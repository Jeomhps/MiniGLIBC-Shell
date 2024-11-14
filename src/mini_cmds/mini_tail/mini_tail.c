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

  char **buffer = mini_calloc(sizeof(char *), n);
  for (int i = 0; i < n; i++) {
    buffer[i] = NULL;
  }

  char line[BUF_SIZE];
  int index = 0;
  int line_count = 0;
  int c;

  while ((c = mini_fgetc(file)) != -1) {
    line[index] = (char)c;
    index++;

    if (c == '\n' || index >= BUF_SIZE - 1) {
      line[index] = '\0';

      if (buffer[line_count % n]) {
        mini_free(buffer[line_count % n]);
      }

      buffer[line_count % n] = mini_calloc(sizeof(char), index + 1);
      if (buffer[line_count % n]) {
        mini_strcpy(buffer[line_count % n], line);
      }

      line_count++;
      index = 0;
    }
  }

  int start = (line_count > n) ? line_count - n : 0;
  for (int i = start; i < line_count; i++) {
    if (buffer[i % n]) {
      mini_printf(buffer[i % n]);
      mini_free(buffer[i % n]);
    }
  }

  mini_free(buffer);
  mini_fclose(file);
  return 0;
}

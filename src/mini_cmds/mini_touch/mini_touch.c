#include "../../mini_glibc/mini_lib.h"
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    mini_printf("Usage: touch <filename>\n");
    return 1;
  }

  char *filename = argv[1];
  MYFILE *file = mini_fopen(filename, 'w');
  if (file == NULL) {
    mini_perror("Error creating the file");
    return 1;
  }

  if (mini_fclose(file) == -1) {
    mini_perror("Error closing the file");
    return 1;
  }

  return 0;
}

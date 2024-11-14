#include <stdlib.h>
#include <sys/stat.h>

#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    mini_printf("Usage : mini_mkdir <dirname>\n");
  }

  int result = mkdir(argv[1], 0777); // Will automatically respect sys umask

  if (result == -1) {
    mini_perror("Error creating directory");
  }

  return 1;
}

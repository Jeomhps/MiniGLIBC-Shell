#include <unistd.h>

#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    mini_printf("Usage : mini_cd <dir> \n");
  }

  if (chdir(argv[1]) != 0) {
    mini_perror("Error : unable to change directory");
    return -1;
  }
  return 0;
}

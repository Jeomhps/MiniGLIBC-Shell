#include <unistd.h>

#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    mini_printf("Usage: mini_ln <source> <destination>\n");
    return 1;
  }

  if (symlink(argv[1], argv[2]) == -1) {
    mini_perror("mini_ln: Error creating symbolic link");
  }

  return 0;
}

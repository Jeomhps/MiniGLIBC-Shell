#include <sys/stat.h>
#include <unistd.h>

#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    mini_printf("Usage : mini_rmdir <dir>\n");
  }
  struct stat dir_stat;

  if (stat(argv[1], &dir_stat) == -1) {
    mini_perror("Error retrieving directory information");
    return 1;
  }

  if (S_ISDIR(dir_stat.st_mode)) {
    if (rmdir(argv[1]) == -1) {
      mini_perror("Error deleting the directory");
    }
  } else {
    mini_printf("The specified path is not a directory. Skipping deletion.\n");
  }

  return 0;
}

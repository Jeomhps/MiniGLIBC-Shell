#include <sys/stat.h>
#include <unistd.h>

#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    mini_printf("Usage : mini_rm <file>\n");
  }
  struct stat file_stat;

  if (stat(argv[1], &file_stat) == -1) {
    mini_perror("Error retrieving file information");
    return 1;
  }

  if (S_ISREG(file_stat.st_mode)) {
    if (unlink(argv[1]) == 0) {
      mini_printf("File deleted successfully.\n");
    }
  } else {
    mini_printf(
        "The specified file is not a regular file. Skipping deletion.\n");
  }

  return 1;
}

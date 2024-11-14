#include <sys/stat.h>

#include "../../mini_glibc/mini_lib.h"

int mini_strtol(char *str) {
  int result = 0;

  while (*str) {
    if (*str < '0' || *str > '7') {
      return -1;
    }
    result = (result << 3) + (*str - '0');
    str++;
  }

  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    mini_printf("Usage: mini_chmod <permissions> <filename>\n");
    mini_exit(1);
  }

  // Use mini_strtol to parse the permissions argument
  int permissions = mini_strtol(argv[1]);
  if (permissions == -1) {
    mini_printf("Invalid octal permissions\n");
    mini_exit(1);
  }

  if (chmod(argv[2], permissions) == -1) {
    mini_perror("mini_chmod: Error changing file permissions");
  }

  return 0;
}

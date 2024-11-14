#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    mini_printf("Usage: mini_clean filename\n");
    return 1;
  }

  MYFILE *file = mini_fopen(argv[1], 'w');
  if (file == NULL) {
    mini_perror("Error opening or creating file");
    return 1;
  }

  mini_fclose(file);

  return 0;
}

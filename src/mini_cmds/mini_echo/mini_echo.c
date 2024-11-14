#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {

  for (int i = 1; i < argc; i++) {
    mini_printf(argv[i]);
    mini_printf(" ");
  }
  mini_printf("\n");
  return 0;
}

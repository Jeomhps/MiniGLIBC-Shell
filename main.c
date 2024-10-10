#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mini_lib.h"

int main(int argc, char *argv[]) {
  printf("%p\n", mini_calloc(4, 2));
  printf("%p\n", sbrk(0));
  return EXIT_SUCCESS;
}

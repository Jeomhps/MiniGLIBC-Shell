#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "mini_lib.h"

#define BUF_SIZE 1024

static char *buffer = NULL;
static int ind = -1;

void mini_printf(char *str) {
  if (ind == -1) {
    buffer = (char *)mini_calloc(sizeof(char), BUF_SIZE);
    ind = 0;
  }

  while (*str) {
    buffer[ind++] = *str;
    // ind++;
    if (ind == BUF_SIZE || *str == '\n') {
      syscall(SYS_write, STDOUT_FILENO, buffer, ind);
      ind = 0;
      memset(buffer, 0, BUF_SIZE);
    }
    str++;
  }
}

void mini_exit_printf(void) {
  if (ind > 0) {
    syscall(SYS_write, STDOUT_FILENO, buffer, ind);
    memset(buffer, 0, ind); // Réinitialiser le tampon après écriture
    ind = 0;
  }
}

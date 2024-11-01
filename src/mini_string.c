#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "mini_lib.h"

#define BUF_SIZE 1024

static char *buffer = NULL;
static int ind = -1;

// extern const char *const _sys_errlist[];
// extern int errno;

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

int mini_scanf(char *buffer, int buffer_size) {
  char c;
  int chars_read = 1; // chars_read start at 1

  while (read(STDIN_FILENO, &c, 1) > 0 && chars_read < buffer_size - 1) {
    *buffer++ = c;
    chars_read++;
  }

  // Flush the overflow by reading all remaining characters from standard input
  while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n') {
    c = '\0'; // Discard the character
  }

  // ioctl(STDIN_FILENO, TCFLSH, TCIFLUSH);
  return (int)chars_read; // Cast to int and return
}

int mini_strlen(char *s) {
  int size = 0;
  while (*s++) {
    size++;
  }
  return size;
}

int mini_strcpy(char *s, char *d) {
  int count = 0;
  while (s[count]) {
    d[count] = s[count];
    count++;
  }

  for (int i = count; i < mini_strlen(d); i++) {
    d[i] = '\0';
  }

  return count;
}

int mini_strcmp(char *s1, char *s2) {
  while (*s1) {
    if (s1++ != s2++) {
      return 1;
    }
    // s1++;
    // s2++;
  }
  return 0;
}

void mini_perror(char *message) {
  mini_printf(message);
  mini_printf(" : ");
  char buffer[20];
  itoa(errno, buffer);
  mini_printf(buffer);
  mini_printf("\n");
}

void itoa(int n, char *buffer) {
  int i = 0;
  int isNeg = 0;

  if (n == 0) {
    buffer[i++] = '0';
    buffer[i] = '\0';
    return;
  }

  if (n < 0) {
    isNeg = 1;
    n = -n;
  }

  while (n != 0) {
    buffer[i++] = (n % 10) + '0';
    n /= 10;
  }

  if (isNeg) {
    buffer[i++] = '-';
  }

  buffer[i] = '\0';

  for (int j = 0; j < i / 2; j++) {
    char temp = buffer[j];
    buffer[j] = buffer[i - j - 1];
    buffer[i - j - 1] = temp;
  }
}

void mini_exit_printf(void) {
  if (ind > 0) {
    syscall(SYS_write, STDOUT_FILENO, buffer, ind);
    memset(buffer, 0, ind);
    ind = 0;
  }
}

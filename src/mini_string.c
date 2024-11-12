#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "mini_lib.h"

#define BUF_SIZE 1024

char *buffer = NULL;
int ind = -1;

void mini_printf(char *str) {
  if (str == NULL) {
    errno = EINVAL;
    return;
  }

  if (ind == -1) {
    buffer = (char *)mini_calloc(sizeof(char), BUF_SIZE);
    if (buffer == NULL) {
      return;
    }

    ind = 0;
  }

  while (*str) {
    buffer[ind] = *str;
    ind++;

    if (ind == BUF_SIZE || *str == '\n') {
      int write_result = write(STDOUT_FILENO, buffer, ind);
      if (write_result < 0) { // Is it really necessary ?
        errno = EIO;
      }

      mini_memset(buffer, '\0', BUF_SIZE);
      ind = 0;
    }
    str++;
  }
}

int mini_scanf(char *buffer, int buffer_size) {
  char c;
  int chars_read = 0;

  while (chars_read < buffer_size - 1) {
    if (read(STDIN_FILENO, &c, 1) <= 0) {
      break;
    }
    if (c == '\n') {
      break;
    }
    *buffer = c;
    buffer++;
    chars_read++;
  }

  *buffer = '\0';

  while (c != '\n' && read(STDIN_FILENO, &c, 1) > 0) {
    // Discard characters until newline
  }

  return chars_read;
}

int mini_strlen(char *s) {
  if (s == NULL)
    return 0;

  int size = 0;
  while (*s++) {
    size++;
  }

  return size;
}

int mini_strcpy(char *d, char *s) {
  if (d == NULL || s == NULL)
    return 0;

  int count = 0;
  while (s[count] != '\0') {
    d[count] = s[count];
    count++;
  }

  d[count] = '\0';
  return count;
}

int mini_strcmp(char *s1, char *s2) {
  if (s1 == NULL && s2 == NULL) {
    return 0;
  }
  if (s1 == NULL) {
    return -1;
  }
  if (s2 == NULL) {
    return 1;
  }

  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }

  return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void mini_perror(char *message) {
  mini_printf(message);
  mini_printf(" : ");
  char buffer[20];
  mini_itoa(errno, buffer);
  mini_printf(buffer);
  mini_printf("\n");
}

void mini_itoa(int n, char *buffer) {
  int i = 0;

  if (n == 0) {
    buffer[i] = '0';
    i++;
    buffer[i] = '\0';
    return;
  }

  int isNegative = n < 0;
  if (isNegative) {
    n = -n;
  }

  while (n > 0) {
    buffer[i] = (n % 10) + '0';
    i++;
    n /= 10;
  }

  if (isNegative) {
    buffer[i] = '-';
    i++;
  }

  buffer[i] = '\0';

  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char tmp = buffer[j];
    buffer[j] = buffer[k];
    buffer[k] = tmp;
  }
}

void mini_exit_printf(void) {
  if (ind > 0) {
    write(STDOUT_FILENO, buffer, ind);
    mini_memset(buffer, '\0', ind);
    ind = 0;
  }
}

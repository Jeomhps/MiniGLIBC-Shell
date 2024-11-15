#include <sys/wait.h>
#include <unistd.h>

#include "mini_glibc/mini_lib.h"

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define PATH_BUFFER_SIZE 1024

char *mini_strcat(char *dest, const char *src) {
  char *original_dest = dest;

  while (*dest) {
    dest++;
  }

  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }

  *dest = '\0';

  return original_dest;
}

char *mini_strpbrk(const char *str, const char *delim) {
  while (*str) {
    const char *d = delim;
    while (*d) {
      if (*str == *d) {
        return (char *)str;
      }
      d++;
    }
    str++;
  }

  return NULL;
}

char *mini_strtok(char *str, const char *delim) {
  static char *next_token = NULL;

  if (str != NULL) {
    next_token = str;
  }

  if (next_token == NULL) {
    return NULL;
  }

  char *start = next_token;

  next_token = mini_strpbrk(next_token, delim);

  if (next_token != NULL) {
    *next_token = '\0';
    next_token++;
  }

  return start;
}

int main(void) {
  char cmd[MAX_CMD_LEN];
  char hostname[1024];
  char cwd[1024];
  char path_buffer[PATH_BUFFER_SIZE]; // Buffer for the constructed path

  gethostname(hostname, sizeof(hostname));

  while (1) {
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
      mini_printf("Erreur : impossible de récupérer le répertoire courant\n");
      continue;
    }

    mini_printf(getlogin());
    mini_printf("@");
    mini_printf(hostname);
    mini_printf(":");
    mini_printf(cwd);
    mini_printf("> ");

    mini_exit_printf();

    if (mini_scanf(cmd, MAX_CMD_LEN) < 0) {
      mini_printf("Erreur de lecture de la commande.\n");
      continue;
    }

    if (mini_strcmp(cmd, "exit") == 0) {
      break;
    }

    char *args[MAX_ARGS];
    int arg_count = 0;
    char *token = mini_strtok(cmd, " ");
    while (token != NULL && arg_count < MAX_ARGS - 1) {
      args[arg_count++] = token;
      token = mini_strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    pid_t pid = fork();

    if (pid == -1) {
      mini_printf("Erreur lors de la création du processus\n");
      continue;
    } else if (pid == 0) {
      // Construct the path to the executable
      mini_strcpy(path_buffer, cwd);
      mini_strcat(path_buffer, "/binary/");
      mini_strcat(path_buffer, args[0]);

      // Use execv with the constructed path
      if (execv(path_buffer, args) == -1) {
        mini_printf("Erreur : commande inconnue \n");
        mini_printf(args[0]);
        mini_exit(1);
      }
    } else {
      int status;
      wait(&status);
    }
  }

  mini_printf("Shell terminé.\n");
  return 0;
}

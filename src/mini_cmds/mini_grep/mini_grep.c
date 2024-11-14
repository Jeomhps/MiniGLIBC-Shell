#include "../../mini_glibc/mini_lib.h"

#define BUF_SIZE 1024

int contains_word(char *line, char *word) {
  int line_len = mini_strlen(line);
  int word_len = mini_strlen(word);

  if (line_len < word_len) {
    return 0; // La ligne est plus courte que le mot
  }

  for (int i = 0; i <= line_len - word_len; i++) {
    int found = 1;
    for (int j = 0; j < word_len; j++) {
      if (line[i + j] != word[j]) {
        found = 0;
        break;
      }
    }
    if (found) {
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    mini_printf("Usage: mini_grep word filename\n");
    return 1;
  }

  char *word = argv[1];
  MYFILE *file = mini_fopen(argv[2], 'r');
  if (file == NULL) {
    mini_perror("Error opening file");
    return 1;
  }

  char buffer[BUF_SIZE];
  int index = 0;
  int c;

  while ((c = mini_fgetc(file)) != -1) {
    buffer[index] = (char)c;
    index++;

    if (c == '\n' || index >= BUF_SIZE - 1) {
      buffer[index] = '\0';

      if (contains_word(buffer, word)) {
        mini_printf(buffer);
      }

      index = 0;
    }
  }

  mini_fclose(file);
  return 0;
}

#include "../../mini_glibc/mini_lib.h"

int is_whitespace(char c) { return (c == ' ' || c == '\t' || c == '\n'); }

int main(int argc, char *argv[]) {
  if (argc != 2) {
    mini_printf("Usage: mini_wc filename\n");
    return 1;
  }

  MYFILE *file = mini_fopen(argv[1], 'r');
  if (file == NULL) {
    mini_perror("Error opening file");
    return 1;
  }

  int c;
  int in_word = 0;
  int word_count = 0;

  while ((c = mini_fgetc(file)) != -1) {
    if (is_whitespace((char)c)) {
      if (in_word) {
        word_count++;
        in_word = 0;
      }
    } else {
      in_word = 1;
    }
  }

  // Special case for last word
  if (in_word) {
    word_count++;
  }

  mini_printf("Word count: ");
  char buffer[32];
  mini_itoa(word_count, buffer);
  mini_printf(buffer);
  mini_printf("\n");

  mini_fclose(file);
  return 0;
}

#include "../../mini_glibc/mini_lib.h"

#define BUFFER_SIZE 8192

int main(int argc, char *argv[]) {

  if (argc < 3) {
    mini_printf("Usage: cp <src> <dest>\n");
    return 1;
  }

  char *src_filename = argv[1];
  char *dest_filename = argv[2];
  char buffer[BUFFER_SIZE];

  MYFILE *src_file = mini_fopen(src_filename, 'r');
  if (src_file == NULL) {
    mini_perror("Error opening file");
    return 1;
  }

  MYFILE *dest_file = mini_fopen(dest_filename, 'w');
  if (dest_file == NULL) {
    mini_perror("Error creating new file");
    return 1;
  }

  int elements;
  while ((elements = mini_fread(buffer, sizeof(char), BUFFER_SIZE, src_file)) >
         0) {
    if (mini_fwrite(buffer, sizeof(char), elements, dest_file) != elements) {
      mini_perror("Failed to write to the destination file");
      mini_fclose(src_file);
      mini_fclose(dest_file);
      return 1;
    }
  }

  if (mini_fclose(src_file) == -1) {
    mini_perror("Failed to close the source file");
    mini_fclose(dest_file);
    return 1;
  }
  if (mini_fclose(dest_file) == -1) {
    mini_perror("Failed to close the destination file");
    return 1;
  }

  return 0;
}

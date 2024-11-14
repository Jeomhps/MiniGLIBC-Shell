#include <unistd.h>

#include "../../mini_glibc/mini_lib.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    mini_printf("Usage : mini_mv <source> <destination> \n");
  }

  MYFILE *source_file = mini_fopen(argv[1], 'r');
  if (source_file == NULL) {
    mini_perror("Error opening source file");
    return 1;
  }

  MYFILE *dest_file = mini_fopen(argv[2], 'w');
  if (dest_file == NULL) {
    mini_perror("Error opening destination file");
    mini_fclose(source_file); // Close the source file
    return 1;
  }

  char buffer[1024];
  int bytes_read, bytes_written;

  while ((bytes_read = mini_fread(buffer, 1, sizeof(buffer), source_file)) >
         0) {
    bytes_written = mini_fwrite(buffer, 1, bytes_read, dest_file);
    if (bytes_written != bytes_read) {
      mini_perror("Error writing to destination file");
      mini_fclose(source_file);
      mini_fclose(dest_file);
      return 1;
    }
  }

  mini_fclose(source_file);
  mini_fclose(dest_file);

  if (unlink(argv[1]) == -1) {
    mini_perror("Error removing source file");
  }

  return 1;
}

#include "../../mini_glibc/mini_lib.h"

#define MAX_LINE_LENGTH 1024

void mini_quickdiff(const char *file1, const char *file2) {
  MYFILE *fp1 = mini_fopen((char *)file1, 'r');
  MYFILE *fp2 = mini_fopen((char *)file2, 'r');

  if (!fp1 || !fp2) {
    mini_printf("Error: Could not open one or both files\n");
    if (fp1)
      mini_fclose(fp1);
    if (fp2)
      mini_fclose(fp2);
    return;
  }

  char line1[MAX_LINE_LENGTH];
  char line2[MAX_LINE_LENGTH];
  int line_number = 1;

  while (1) {
    int index1 = 0;
    int index2 = 0;
    int c1, c2;

    while ((c1 = mini_fgetc(fp1)) != 0 && c1 != '\n' &&
           index1 < MAX_LINE_LENGTH - 1) {
      line1[index1++] = (char)c1;
    }
    line1[index1] = '\0';

    while ((c2 = mini_fgetc(fp2)) != 0 && c2 != '\n' &&
           index2 < MAX_LINE_LENGTH - 1) {
      line2[index2++] = (char)c2;
    }
    line2[index2] = '\0';

    if (c1 == 0 && c2 == 0)
      break;

    char line_num_str[12];
    if (mini_strcmp(line1, line2) != 0) {
      mini_printf("Difference at line ");
      mini_itoa(line_number, line_num_str);
      mini_printf(line_num_str);
      mini_printf(":\nFile 1: ");
      mini_printf(line1);
      mini_printf("\nFile 2: ");
      mini_printf(line2);
      mini_printf("\n");
    }

    line_number++;

    if (c1 == -1 || c2 == -1) {
      if (c1 != -1) {
        mini_printf("Extra lines in ");
        mini_printf((char *)file1);
        mini_printf(" starting at line ");
        mini_itoa(line_number, line_num_str);
        mini_printf(line_num_str);
        mini_printf(":\n");
        do {
          mini_printf(line1);
          mini_printf("\n");
          index1 = 0;
          while ((c1 = mini_fgetc(fp1)) != -1 && c1 != '\n' &&
                 index1 < MAX_LINE_LENGTH - 1) {
            line1[index1++] = (char)c1;
          }
          line1[index1] = '\0';
          line_number++;
        } while (c1 != -1);
      }

      if (c2 != -1) {
        mini_printf("Extra lines in ");
        mini_printf((char *)file2);
        mini_printf(" starting at line ");
        mini_itoa(line_number, line_num_str);
        mini_printf(line_num_str);
        mini_printf(":\n");
        do {
          mini_printf(line2);
          mini_printf("\n");
          index2 = 0;
          while ((c2 = mini_fgetc(fp2)) != -1 && c2 != '\n' &&
                 index2 < MAX_LINE_LENGTH - 1) {
            line2[index2++] = (char)c2;
          }
          line2[index2] = '\0';
          line_number++;
        } while (c2 != -1);
      }

      break;
    }
  }

  mini_fclose(fp1);
  mini_fclose(fp2);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    mini_printf("Usage: mini_quickdiff <source_file> <destination_file>\n");
    mini_exit(1);
  }

  mini_quickdiff(argv[1], argv[2]);

  return 0;
}

#include <errno.h>
#include <stdlib.h>

#include "mini_lib.h"

void test_mini_memory(void) {
  mini_printf("Testing mini_memory functions with comprehensive checks...\n\n");

  /*
  /-------------------------------------------------
  /       Test mini_calloc with valid inputs
  /-------------------------------------------------
  /
  / Allocate memory blocks using mini_calloc for
  / different sizes and verify that allocations
  / are successful.
  */
  int *arr1 = (int *)mini_calloc(sizeof(int), 5);
  int *arr2 = (int *)mini_calloc(sizeof(int), 10);
  int *arr3 = (int *)mini_calloc(sizeof(int), 15);

  if (arr1 == NULL) {
    mini_perror("Initial mini_calloc allocation for arr1 failed");
  }
  if (arr2 == NULL) {
    mini_perror("Initial mini_calloc allocation for arr2 failed");
  }
  if (arr3 == NULL) {
    mini_perror("Initial mini_calloc allocation for arr3 failed");
  }

  void *first_address = arr1;
  void *second_address = arr2;
  void *third_address = arr3;

  mini_free(arr1);
  mini_free(arr2);
  mini_free(arr3);

  /*
  /-------------------------------------------------
  /       Test reallocation of freed memory blocks
  /-------------------------------------------------
  /
  / Allocate memory blocks again using mini_calloc
  / and verify that they are reallocated to the
  / previously freed memory addresses.
  */
  int *arr4 = (int *)mini_calloc(sizeof(int), 10);
  if (arr4 == NULL) {
    mini_perror("Mini calloc 4 failed");
  } else if (arr4 != second_address) {
    mini_perror("Reallocation 1 of free block failed");
  }

  int *arr5 = (int *)mini_calloc(sizeof(int), 5);
  if (arr5 == NULL) {
    mini_perror("Mini calloc 5 failed");
  } else if (arr5 != first_address) {
    mini_perror("Reallocation 2 of free block failed");
  }

  int *arr6 = (int *)mini_calloc(sizeof(int), 15);
  if (arr6 == NULL) {
    mini_perror("Mini calloc 6 failed");
  } else if (arr6 != third_address) {
    mini_perror("Reallocation 3 of free block failed");
  }

  /*
  /-------------------------------------------------
  /       Test mini_calloc with invalid inputs
  /-------------------------------------------------
  /
  / Test invalid input parameters such as negative
  / or zero sizes and check if errno is correctly
  / set to EINVAL.
  */
  int *t1 = (int *)mini_calloc(sizeof(int), -5);
  if (t1 == NULL) {
    if (errno != EINVAL) {
      mini_perror("EINVAL check for mini_calloc with negative size failed");
    }
  }

  int *t2 = (int *)mini_calloc(-1, 10);
  if (t2 == NULL) {
    if (errno != EINVAL) {
      mini_perror(
          "EINVAL check for mini_calloc with negative element size failed");
    }
  }

  int *t3 = (int *)mini_calloc(0, 10);
  if (t3 == NULL) {
    if (errno != EINVAL) {
      mini_perror("EINVAL check for mini_calloc with zero size_element failed");
    }
  }

  int *t4 = (int *)mini_calloc(10, 0);
  if (t4 == NULL) {
    if (errno != EINVAL) {
      mini_perror(
          "EINVAL check for mini_calloc with zero number_element failed");
    }
  }

  /*
  /-------------------------------------------------
  /       Test mini_free with special cases
  /-------------------------------------------------
  /
  / Test freeing of a null pointer and an invalid
  / pointer that was not allocated using mini_calloc.
  */
  mini_free(NULL); // Should not set errno, just return without doing anything

  // Test mini_free with a pointer that hasn't been allocated by mini_calloc
  int dummy;
  mini_free(&dummy);
  if (errno != EINVAL) {
    mini_perror("mini_free invalid pointer check failed");
  }

  mini_printf("All tests for mini_memory completed\n");
}

void test_mini_string(void) {
  mini_printf("Testing mini_io and mini_string functions...\n");
  mini_printf("\n");

  /*
  /-------------------------------------------------
  /       Test mini_printf with valid input
  /-------------------------------------------------
  /
  / Call mini_printf to print a valid string and
  / observe the expected output. This test ensures
  / that strings are correctly buffered and flushed.
  */
  mini_printf("Testing mini_printf: Hello, mini_lib!\n");
  mini_printf("\n");

  /*
  /-------------------------------------------------
  /       Test mini_printf with NULL input
  /-------------------------------------------------
  /
  / Attempt to print a NULL string using mini_printf.
  / Check that errno is set to EINVAL (22).
  */
  errno = 0;
  mini_printf(NULL);
  if (errno != EINVAL) {
    mini_perror("mini_printf NULL input failed");
  }

  /*
  /-------------------------------------------------
  /       Test mini_scanf for input reading
  /-------------------------------------------------
  /
  / Use mini_scanf to read input from stdin into
  / a buffer. This test verifies that mini_scanf
  / correctly handles buffer sizes and input limits.
  */
  char input_buffer[20];
  mini_printf("Please enter a string of max 19 char for mini_scanf testing:\n");
  int chars_read = mini_scanf(input_buffer, 20);
  mini_printf("Characters read: ");
  char char_read_str[20];
  mini_itoa(chars_read, char_read_str);
  mini_printf(char_read_str);
  mini_printf("\nInput captured: ");
  mini_printf(input_buffer);
  mini_printf("\n");
  mini_printf("\n");

  /*
  /-------------------------------------------------
  /       Test mini_strlen with valid and NULL input
  /-------------------------------------------------
  /
  / Test mini_strlen with a valid string and a NULL
  / input to ensure that string lengths are computed
  / correctly, with special handling for NULL.
  */
  char test_string[] = "mini_strlen test string"; // 23 char
  int len = mini_strlen(test_string);
  if (len != 23) {
    mini_perror("mini_strlen failed to retrieve 23 char");
  }

  len = mini_strlen(NULL);
  if (len != 0) {
    mini_perror("Mini_strlen failed to get the length of NULL string");
  }

  /*
  /-------------------------------------------------
  /       Test mini_strcpy for string copying
  /-------------------------------------------------
  /
  / Copy a string using mini_strcpy and verify that
  / the destination buffer contains the correct copy.
  */
  char src[] = "mini_strcpy source string"; // 25 char
  char dest[1024];
  int copied_chars = mini_strcpy(dest, src);

  if (mini_strcmp(src, dest) != 0) {
    mini_perror("mini_strcpy failed");
  }

  /*
  /-------------------------------------------------
  /       Test mini_strcpy with NULL input
  /-------------------------------------------------
  /
  / Attempt to copy strings with NULL input parameters
  / and verify the behavior of mini_strcpy.
  */
  copied_chars = mini_strcpy(NULL, src);
  if (copied_chars != 0) {
    mini_perror("mini_strcpy NULL destination failed");
  }
  copied_chars = mini_strcpy(dest, NULL);
  if (copied_chars != 0) {
    mini_perror("mini_strcpy NULL source failed");
  }

  /*
  /-------------------------------------------------
  /       Test mini_strcmp for string comparison
  /-------------------------------------------------
  /
  / Compare strings using mini_strcmp and verify that
  / it returns the correct comparison result for
  / identical, different, and NULL input strings.
  */
  int cmp_result = mini_strcmp("abc", "abc");
  if (cmp_result != 0) {
    mini_perror("Strcmp failed for identical string \n");
  }

  cmp_result = mini_strcmp("abc", "def");
  if (cmp_result != -3) {
    mini_perror("Strcmp failed for different string \n");
  }

  cmp_result = mini_strcmp(NULL, "abc");
  if (cmp_result != -1) {
    mini_perror("Strcmp failed for NULL string \n");
  }

  cmp_result = mini_strcmp(NULL, NULL);
  if (cmp_result != 0) {
    mini_perror("Strcmp failed for two NULL string \n");
  }

  /*
  /-------------------------------------------------
  /       Test mini_perror for error messages
  /-------------------------------------------------
  /
  / Set an error code and use mini_perror to display
  / a formatted error message, including the error
  / code number.
  */
  errno = 0;
  mini_perror("Test mini_perror output");
  mini_printf("\n");

  /*
  /-------------------------------------------------
  /       Test mini_itoa for integer-to-string conversion
  /-------------------------------------------------
  /
  / Convert various integers (including zero and
  / negative numbers) to strings using mini_itoa.
  */
  char buffer[20];
  mini_itoa(12345, buffer);

  if (mini_strcmp(buffer, "12345") != 0) {
    mini_perror("Mini_itoa for positive integer failed");
  }

  mini_itoa(-54321, buffer);
  if (mini_strcmp(buffer, "-54321") != 0) {
    mini_perror("Mini_itoa for negative integer failed");
  }

  mini_itoa(0, buffer);
  if (mini_strcmp(buffer, "0") != 0) {
    mini_perror("Mini_itoa for NULL integer failed");
  }

  /*
  /-------------------------------------------------
  /       Test mini_exit_printf for final buffer flush
  /-------------------------------------------------
  /
  / Ensure that mini_exit_printf flushes any remaining
  / data in the buffer to standard output before exiting.
  */
  mini_printf("Final message before mini_exit_printf, should be printed even "
              "without \\n");
  mini_exit_printf();

  mini_printf("\n\n");

  mini_printf("All tests for mini_string completed\n");
}

void test_mini_io2(void) {
  mini_printf("Testing mini_io functions with comprehensive checks...\n\n");

  /*
  /-------------------------------------------------
  /       Test mini_fopen with valid inputs
  /-------------------------------------------------
  /
  / Open files in different modes and check that
  / file descriptors are valid.
  */
  MYFILE *file_r = mini_fopen("tests_file/testfile_read.txt", 'r');
  if (file_r == NULL) {
    mini_perror("mini_fopen failed to open file in read mode");
  }

  MYFILE *file_w = mini_fopen("tests_file/testfile_write.txt", 'w');
  if (file_w == NULL) {
    mini_perror("mini_fopen failed to open file in write mode");
  }

  MYFILE *file_b = mini_fopen("tests_file/testfile_rw.txt", 'b');
  if (file_b == NULL) {
    mini_perror("mini_fopen failed to open file in read/write mode");
  }

  MYFILE *file_a = mini_fopen("tests_file/testfile_append.txt", 'a');
  if (file_a == NULL) {
    mini_perror("mini_fopen failed to open file in append mode");
  }

  /*
  /-------------------------------------------------
  /       Test mini_fopen with invalid inputs
  /-------------------------------------------------
  /
  / Open files with invalid modes and check that
  / errno is correctly set.
  */
  MYFILE *file_invalid = mini_fopen("tests_file/testfile_invalid.txt", 'z');
  if (file_invalid != NULL || errno != EINVAL) {
    mini_perror("mini_fopen with invalid param failed \n");
  }

  /*
  /-------------------------------------------------
  /       Test mini_fwrite with valid inputs
  /-------------------------------------------------
  /
  / Write data to files using mini_fwrite and verify
  / the number of elements written.
  */
  char write_data[] = "Hello, mini_io!";
  int elements_written =
      mini_fwrite(write_data, sizeof(char), sizeof(write_data) - 1, file_w);
  if (elements_written != sizeof(write_data) - 1) {
    mini_perror("mini_fwrite wrote incorrect number of elements");
  }

  /*
  /-------------------------------------------------
  /       Test mini_fread with valid inputs
  /-------------------------------------------------
  /
  / Read data from files using mini_fread and verify
  / the number of elements read.
  */
  mini_fclose(file_w); // Close and reopen in read mode for reading
  MYFILE *file_read = mini_fopen("tests_file/testfile_write.txt", 'r');
  char read_buffer[64] = {0};
  int elements_read =
      mini_fread(read_buffer, sizeof(char), sizeof(write_data) - 1, file_read);
  if (elements_read != sizeof(write_data) - 1) {
    mini_perror("mini_fread read incorrect number of elements");
  }

  /*
  /-------------------------------------------------
  /       Test mini_fgetc and mini_fputc
  /-------------------------------------------------
  /
  / Write a character using mini_fputc and read it
  / back using mini_fgetc.
  */
  char test_char = 'M';
  int fputc_result = mini_fputc(file_b, test_char);
  if (fputc_result != (unsigned char)test_char) {
    mini_perror("mini_fputc failed to write character");
  }
  mini_fclose(file_b);

  MYFILE *file_char = mini_fopen("tests_file/testfile_rw.txt", 'r');
  int fgetc_result = mini_fgetc(file_char);
  if (fgetc_result != test_char) {
    mini_perror("mini_fgetc failed to read correct character");
  }

  /*
  /-------------------------------------------------
  /       Test mini_fflush
  /-------------------------------------------------
  /
  / Flush buffer contents using mini_fflush and
  / ensure data integrity.
  */
  mini_fwrite(write_data, sizeof(char), sizeof(write_data) - 1, file_a);
  if (mini_fflush(file_a) == -1) {
    mini_perror("mini_fflush failed");
  }

  /*
  /-------------------------------------------------
  /       Test mini_fclose
  /-------------------------------------------------
  /
  / Close open files and verify proper cleanup.
  */
  if (mini_fclose(file_r) != 42) {
    mini_perror("mini_fclose failed for read file");
  }
  if (mini_fclose(file_read) != 42) {
    mini_perror("mini_fclose failed for write file");
  }
  if (mini_fclose(file_a) != 42) {
    mini_perror("mini_fclose failed for append file");
  }
  if (mini_fclose(file_char) != 42) {
    mini_perror("mini_fclose failed for character file");
  }

  /*
  /-------------------------------------------------
  /       Test mini_io_exit for cleanup
  /-------------------------------------------------
  /
  / Call mini_io_exit to ensure all files are closed
  / and buffers are freed.
  */
  mini_io_exit();

  mini_printf("mini_io_exit successfully cleaned up resources\n");
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  test_mini_memory();

  mini_printf("\n");

  test_mini_string();

  mini_printf("\n");

  test_mini_io2();

  mini_exit(0);
}

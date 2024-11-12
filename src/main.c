#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mini_lib.h"

void test_mini_memory(void) {
  printf("Testing mini_memory functions with comprehensive checks...\n");

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

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  test_mini_memory();

  /*char *str = "Bonjour le monde \ntata \ntoto \nbonjour";
  mini_printf(str);
  mini_printf("\ntest \n");*/

  mini_printf("Hello world \n");

  // Used for testing purpose to understand how to flush the buffer
  // May be interesting to write a note about this
  /*while (*str) {
    putchar(*str);
    str++;
  }

  fflush(stdout); */

  char *myBuf = (char *)mini_calloc(sizeof(char), 5);

  // mini_scanf(myBuf, 6);

  // mini_printf(myBuf);
  // mini_printf("\n");
  // printf("%i\n", mini_strlen(myBuf));

  // char *s = "oui";

  // printf("%i\n", mini_strlen(s));
  // mini_strcpy(s, myBuf);
  // mini_printf(myBuf);

  // mini_printf("\n");

  // int test = mini_strcmp("oui", "ooi");
  // printf("%i\n", test);

  // mini_perror("bonjour");

  int i = -132;

  mini_itoa(i, myBuf);

  mini_printf(myBuf);
  mini_printf("\n");

  mini_perror("test");

  MYFILE *file = mini_fopen("example.txt", 'r');
  if (file == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
  }

  // char buffer[4000];
  // int elements_read = mini_fread(buffer, 1, 4000, file);
  // if (elements_read < 0) {
  //   perror("Erreur lors de la lecture du fichier");
  //   return 1;
  // }
  //
  // buffer[elements_read] = '\0';
  // printf("Contenu lu :\n%s\n", buffer);

  mini_perror("oui");

  MYFILE *myfile = mini_fopen("/mnt/test/test_output.txt", 'w');
  if (myfile == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
  }

  MYFILE *myfile2 = mini_fopen("/mnt/test/test_output2.txt", 'w');
  if (myfile == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
  }

  char data[] =
      "Ceci est un test de mini_fwrite. Ce texte devrait être écrit "
      "dans le fichier. "
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

  int elements_written =
      mini_fwrite(data, sizeof(char), sizeof(data) - 1, myfile);
  if (elements_written < 0) {
    perror("Erreur lors de l'écriture avec mini_fwrite");
    return 1;
  }

  printf("Nombre d'éléments écrits : %d\n", elements_written);

  int elements_written2 =
      mini_fwrite(data, sizeof(char), sizeof(data) - 1, myfile2);
  if (elements_written2 < 0) {
    perror("Erreur lors de l'écriture avec mini_fwrite");
    return 1;
  }

  printf("Nombre d'éléments écrits : %d\n", elements_written2);

  // mini_fflush(myfile);
  // char a[2];
  // a[0] = mini_fgetc(file);
  // a[1] = '\0';
  char a[100];

  for (int i = 0; i < 40; i++) {
    a[i] = mini_fgetc(file);
  }
  a[40] = '\0';

  mini_fflush(file);
  mini_printf(a);
  mini_printf("\n");
  mini_fclose(myfile);

  mini_fputc(myfile2, 'c');
  mini_fputc(myfile2, EOF);
  mini_fputc(myfile2, 'c');
  mini_fputc(myfile2, 'c');
  mini_fputc(myfile2, EOF);

  mini_exit(0);

  return 0;

  mini_exit(0);
}

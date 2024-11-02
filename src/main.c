#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mini_lib.h"

int main(int argc, char *argv[]) {
  // Allocated memory for my 3 arrays
  int *arr1 = (int *)mini_calloc(sizeof(int), 5);
  int *arr2 = (int *)mini_calloc(sizeof(int), 10);
  int *arr3 = (int *)mini_calloc(sizeof(int), 20);

  // Verify the mini_calloc did not fail
  assert(arr1 != NULL);
  assert(arr2 != NULL);
  assert(arr3 != NULL);

  // Verify the memory has been initalized with '\0's
  for (int i = 0; i < 5; i++) {
    assert(*(arr1 + i) == '\0');
  }

  for (int i = 0; i < 10; i++) {
    assert(*(arr2 + i) == '\0');
  }

  for (int i = 0; i < 20; i++) {
    assert(*(arr3 + i) == '\0');
  }

  // Store the addresses of the memory block allocated
  void *first_address = arr1;
  void *second_address = arr2;
  void *third_address = arr3;

  // Free all my allocated blocks
  mini_free(arr1);
  mini_free(arr2);
  mini_free(arr3);

  // Test : whether the new allocation will use the second freed block
  // (size of allocation == size of freed block)
  int *arr4 = (int *)mini_calloc(sizeof(int), 10);
  assert(arr4 != NULL);
  assert(arr4 == second_address);

  // Test : whether the new allocation will use the first freed block
  // (size of allocation == size of freed block)
  int *arr5 = (int *)mini_calloc(sizeof(int), 5);
  assert(arr5 != NULL);
  assert(arr5 == first_address);

  // Test : whether the new allocation will use the third freed block
  // (size smaller than the new required size for allocation)
  int *arr6 = (int *)mini_calloc(sizeof(int), 15);
  assert(arr6 != NULL);
  assert(arr6 == third_address);

  // Free the memory
  mini_free(arr4);
  mini_free(arr5);
  mini_free(arr6);

  printf("Every assertion succeeded !\n");

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

  itoa(i, myBuf);

  mini_printf(myBuf);
  mini_printf("\n");

  mini_perror("test");

  MYFILE *file = mini_fopen("example.txt", 'r');
  if (file == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
  }

  char buffer[4000];
  int elements_read = mini_fread(buffer, 1, 4000, file);
  if (elements_read < 0) {
    perror("Erreur lors de la lecture du fichier");
    return 1;
  }

  buffer[elements_read] = '\0';
  printf("Contenu lu :\n%s\n", buffer);

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
  mini_exit();

  return 0;

  mini_exit();
}

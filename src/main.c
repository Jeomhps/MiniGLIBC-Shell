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

  mini_exit();
}

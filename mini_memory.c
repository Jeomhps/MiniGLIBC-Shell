#include <stdio.h>
#include <unistd.h>

void *mini_calloc(int size_element, int number_element) {
  size_t total_size = size_element * number_element;

  void *old_break = sbrk(0);

  void *allocated_memory = sbrk(size_element * number_element);

  if (allocated_memory == (void *)-1) {
    // If sbrk returns (void*)-1, it means the allocation failed
    perror("sbrk failed");
    return NULL;
  }

  void *new_break = sbrk(0);

  size_t allocated_size = (char *)new_break - (char *)old_break;

  if (allocated_size != total_size) {
    // If the allocated size is incorrect, print an error and return NULL
    printf("Error: Incorrect allocation size. Expected %zu bytes, but got %zu "
           "bytes.\n",
           total_size, allocated_size);
    return NULL;
  }

  return allocated_memory;
}

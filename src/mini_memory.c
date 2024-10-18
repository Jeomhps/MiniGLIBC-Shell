#include <stdio.h>
#include <unistd.h>

#include "mini_lib.h"

typedef struct malloc_element {
  void *memory_ptr;
  size_t size;
  int status; // 0 for free, 1 for used
  struct malloc_element *next;
} malloc_element;

static malloc_element *malloc_list = NULL; // Contains all malloc element

void *mini_calloc(int size_element, int number_element) {
  size_t total_size = size_element * number_element;

  malloc_element *current = malloc_list;

  // Looks for a free data block with enough space
  while (current != NULL) {
    if (current->status == 0 && current->size >= total_size) {
      current->status = 1;

      // Re-initialize memory to '\0'
      for (size_t i = 0; i < current->size; i++) {
        *(char *)(current->memory_ptr + i) = '\0';
      }

      // Check if Re-initialisation went as expected
      for (size_t i = 0; i < current->size; i++) {
        if (*(char *)(current->memory_ptr + i) != '\0') {
          printf("Memory check failed at index %zu: value is %d, expected 0\n",
                 i, *(char *)(current->memory_ptr + i));
          return NULL;
        }
      }

      return current->memory_ptr;
    }
    current = current->next;
  }

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

  // Allocation of the space for the metadatas of the new element
  malloc_element *new_element = sbrk(sizeof(malloc_element));
  if (new_element == (void *)-1) {
    perror("sbrk failed to allocate memory for malloc_element");
    return NULL;
  }

  // Initialisation of the values according to the data allocatd
  new_element->memory_ptr = allocated_memory;
  new_element->size = total_size;
  new_element->status = 1;
  new_element->next = NULL;

  // Add the new element to the end of the linked list
  if (malloc_list == NULL) {
    malloc_list = new_element;
  } else {
    malloc_element *temp = malloc_list;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_element;
  }

  // Initialisation of memory to '\0'
  for (size_t i = 0; i < total_size; i++) {
    *(char *)(allocated_memory + i) = '\0';
  }

  // Verifies that the initialisation went as planned
  for (size_t i = 0; i < total_size; i++) {
    if (*(char *)(allocated_memory + i) != '\0') {
      printf("Memory check failed at index %zu: value is %d, expected 0\n", i,
             *(char *)(allocated_memory + i));
      return NULL;
    }
  }
  return allocated_memory;
}

void mini_free(void *ptr) {
  malloc_element *current_element = malloc_list;

  // Search for the given data block
  while (current_element != NULL) {
    if (current_element->memory_ptr == ptr) {
      current_element->status = 0; // Mark it as free
      return;
    }
    current_element = current_element->next;
  }
  printf("Error: Unable to free memory. Pointer not found.\n");
}

void mini_exit(void) {
  mini_exit_printf();
  _exit(0);
}

#include <errno.h>
#include <unistd.h>

#include "mini_lib.h"

typedef struct malloc_element {
  void *memory_ptr;
  int size;
  int status;
  struct malloc_element *next;
} malloc_element;

malloc_element *malloc_list = NULL;

void *mini_calloc(int size_element, int number_element) {
  if (size_element <= 0 || number_element <= 0) {
    errno = EINVAL;
    return NULL;
  }

  int total_size = size_element * number_element;

  malloc_element *current_element = malloc_list;
  while (current_element != NULL) {
    if (current_element->status == 0 && current_element->size >= total_size) {
      current_element->status = 1;
      mini_memset(current_element->memory_ptr, '\0', total_size);
      return current_element->memory_ptr;
    }
    current_element = current_element->next;
  }

  void *allocated_memory = sbrk(total_size);
  if (allocated_memory == (void *)-1) {
    return NULL;
  }

  malloc_element *new_element = sbrk(sizeof(malloc_element));
  if (new_element == (void *)-1) {
    return NULL;
  }

  new_element->memory_ptr = allocated_memory;
  new_element->size = total_size;
  new_element->status = 1;
  new_element->next = NULL;

  if (malloc_list == NULL) {
    malloc_list = new_element;
  } else {
    malloc_element *temp = malloc_list;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_element;
  }

  mini_memset(allocated_memory, '\0', total_size);

  return allocated_memory;
}

void mini_free(void *ptr) {
  if (ptr == NULL) {
    return;
  }

  malloc_element *current_element = malloc_list;

  while (current_element != NULL) {
    if (current_element->memory_ptr == ptr) {
      if (current_element->status == 0) {
        return;
      }

      current_element->status = 0;
      return;
    }
    current_element = current_element->next;
  }

  errno = EINVAL;
}

void *mini_memset(void *ptr, int value, int size) {
  unsigned char *p = (unsigned char *)ptr;
  for (int i = 0; i < size; i++) {
    p[i] = (unsigned char)value;
  }
  return ptr;
}

void mini_exit(int status) {
  mini_exit_printf();
  mini_io_exit();
  _exit(status);
}

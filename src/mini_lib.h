#ifndef MINI_LIB

void *mini_calloc(int size_element, int number_element);
void mini_free(void *ptr);
void mini_exit(void);

// Function of stdio
void mini_printf(char *str);
int mini_scanf(char *buffer, int buffer_size);
int mini_strlen(char *str);
void mini_exit_printf(void);

#endif // !MINI_LIB.H

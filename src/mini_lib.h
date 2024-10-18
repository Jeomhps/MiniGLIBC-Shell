#ifndef MINI_LIB

void *mini_calloc(int size_element, int number_element);
void mini_free(void *ptr);
void mini_exit(void);

// Function of stdio
void mini_printf(char *str);
void mini_exit_printf(void);

#endif // !MINI_LIB.H

#ifndef MINI_LIB

void *mini_calloc(int size_element, int number_element);
void mini_free(void *ptr);
void mini_exit(void);

// Function of stdio
void mini_printf(char *str);
int mini_scanf(char *buffer, int buffer_size);
int mini_strlen(char *str);
int mini_strcpy(char *s, char *d);
int mini_strcmp(char *s1, char *s2);
void mini_exit_printf(void);

#endif // !MINI_LIB.H

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
void mini_perror(char *message);
void itoa(int n, char *buffer);
void mini_exit_printf(void);

// stdio
typedef struct MYFILE MYFILE;

MYFILE *mini_fopen(char *file, char mode);
int mini_fread(void *buffer, int size_element, int number_element,
               MYFILE *file);

#endif // !MINI_LIB.H

#ifndef MINI_LIB

// Mini_memory.c
void *mini_calloc(int size_element, int number_element);
void mini_free(void *ptr);
void *mini_memset(void *ptr, int value, int size);
void mini_exit(int status);

// Function of stdio
void mini_printf(char *str);
int mini_scanf(char *buffer, int buffer_size);
int mini_strlen(char *str);
int mini_strcpy(char *s, char *d);
int mini_strcmp(char *s1, char *s2);
void mini_perror(char *message);
void mini_itoa(int n, char *buffer);
void mini_exit_printf(void);

// stdio
typedef struct MYFILE MYFILE;

MYFILE *mini_fopen(char *file, char mode);
int mini_fread(void *buffer, int size_element, int number_element,
               MYFILE *file);
int mini_fwrite(void *buffer, int size_element, int number_element,
                MYFILE *file);
int mini_fflush(MYFILE *file);
int mini_fclose(MYFILE *file);
int mini_fgetc(MYFILE *file);
int mini_fputc(MYFILE *file, char c);
void mini_io_exit(void);

#endif // !MINI_LIB.H

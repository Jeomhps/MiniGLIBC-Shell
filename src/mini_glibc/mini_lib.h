#ifndef MINI_LIB

/*
/-------------------------------------------------
/       Mini_memory.c
/-------------------------------------------------
*/

/*
 * mini_calloc - Allocates and initializes a contiguous block of memory.
 *
 * @size_element: The size (in bytes) of each element to allocate.
 * @number_element: The number of elements to allocate.
 *
 * This function behaves similarly to the standard `calloc()`, but it is
 * implemented using a custom memory allocation strategy. It searches for free
 * memory blocks in a linked list and reuses them if possible. Otherwise, it
 * allocates new memory using `sbrk()`. The allocated memory is initialized to
 * zero.
 *
 * Returns: Pointer to the allocated memory block, or NULL if the allocation
 * fails. Sets `errno` to `EINVAL` if the input sizes are invalid.
 */
void *mini_calloc(int size_element, int number_element);

/*
 * mini_free - Frees a previously allocated memory block.
 *
 * @ptr: Pointer to the memory block to be freed.
 *
 * This function marks the memory block as free in the custom memory
 * management system. If the memory block is already free or if the pointer is
 * NULL, no action is taken. If the pointer does not correspond to a valid
 * allocation, `errno` is set to `EINVAL`.
 */
void mini_free(void *ptr);

/*
 * mini_memset - Sets a memory block to a specified value.
 *
 * @ptr: Pointer to the memory block.
 * @value: The value to set each byte of the memory block.
 * @size: The number of bytes to set.
 *
 * This function works similarly to the standard `memset()`, setting each byte
 * of the memory block to the given value.
 *
 * Returns: A pointer to the memory block.
 */
void *mini_memset(void *ptr, int value, int size);

/*
 * mini_exit - Terminates the program with a given exit status.
 *
 * @status: The exit status to return.
 *
 * This function calls custom cleanup functions `mini_exit_printf()` and
 * `mini_io_exit()` before calling the `_exit()` system call to terminate the
 * program with the specified status.
 */
void mini_exit(int status);

/*
/-------------------------------------------------
/       Mini_string.c
/-------------------------------------------------
*/

/*
 * mini_printf - Custom implementation of a simple formatted string output
 * function.
 *
 * @str: The string to print to standard output.
 *
 * This function outputs a string to standard output using a buffer. If the
 * buffer becomes full or a newline character is encountered, the contents are
 * flushed to standard output. The function uses `mini_calloc()` to allocate
 * buffer memory.
 *
 * If the input string is NULL, `errno` is set to `EINVAL`.
 */
void mini_printf(char *str);

/*
 * mini_scanf - Custom implementation of a simple input function.
 *
 * @buffer: The buffer where the input will be stored.
 * @buffer_size: The size of the buffer.
 *
 * Reads input from standard input until a newline or the buffer limit is
 * reached. Additional input after the buffer size is discarded until a newline
 * character is read.
 *
 * Returns: The number of characters read into the buffer (excluding the null
 * terminator).
 */
int mini_scanf(char *buffer, int buffer_size);

/*
 * mini_strlen - Calculates the length of a string.
 *
 * @s: Pointer to the string.
 *
 * Returns: The number of characters in the string, excluding the null
 * terminator. Returns 0 if the input string is NULL.
 */
int mini_strlen(char *str);

/*
 * mini_strcpy - Copies a string from source to destination.
 *
 * @d: Destination buffer.
 * @s: Source string.
 *
 * Copies the string pointed to by `s` to the buffer `d`, including the null
 * terminator.
 *
 * Returns: The number of characters copied (excluding the null terminator).
 *          Returns 0 if either input is NULL.
 */
int mini_strcpy(char *s, char *d);

/*
 * mini_strcmp - Compares two strings lexicographically.
 *
 * @s1: First string.
 * @s2: Second string.
 *
 * Compares `s1` and `s2` and returns an integer less than, equal to, or greater
 * than zero if `s1` is found, respectively, to be less than, to match, or be
 * greater than `s2`.
 *
 * Returns: 0 if both strings are NULL, -1 if only `s1` is NULL, 1 if only `s2`
 * is NULL, or the difference between the first differing characters if neither
 * is NULL.
 */
int mini_strcmp(char *s1, char *s2);

/*
 * mini_perror - Prints an error message followed by the current errno value.
 *
 * @message: Custom error message to display.
 *
 * This function prints the provided error message, followed by a colon, the
 * current errno value, and a newline.
 */
void mini_perror(char *message);

/*
 * mini_itoa - Converts an integer to a string representation.
 *
 * @n: The integer to convert.
 * @buffer: Buffer to store the string representation.
 *
 * Converts the integer `n` to a null-terminated string and stores it in
 * `buffer`.
 */
void mini_itoa(int n, char *buffer);

/*
 * mini_exit_printf - Flushes the buffer used by mini_printf() before exit.
 *
 * If there is any remaining content in the buffer, it is written to standard
 * output.
 */
void mini_exit_printf(void);

/*
/-------------------------------------------------
/       Mini_io.c
/-------------------------------------------------
*/

/*
 * Struct representing a custom file structure for reading and writing
 * operations.
 */
typedef struct MYFILE MYFILE;

/*
 * mini_fopen - Opens a file with a specified mode.
 *
 * @file: Name of the file to be opened.
 * @mode: Mode in which to open the file ('r' for read, 'w' for write, 'b' for
 * read/write, 'a' for append).
 *
 * This function allocates memory for a MYFILE struct, initializes it, and opens
 * the specified file with the provided mode. Supported modes are read ('r'),
 * write ('w'), read/write ('b'), and append ('a').
 *
 * Returns: Pointer to the MYFILE struct if successful, NULL on failure.
 */
MYFILE *mini_fopen(char *file, char mode);

/*
 * mini_fread - Reads data from a MYFILE object into a buffer.
 *
 * @buffer: Destination buffer to store the read data.
 * @size_element: Size of each element to be read.
 * @number_element: Number of elements to be read.
 * @file: Pointer to the MYFILE object from which to read.
 *
 * Reads up to `number_element` elements of size `size_element` from the given
 * MYFILE object. Data is read from an internal buffer, and the buffer is
 * refilled when necessary.
 *
 * Returns: Number of elements successfully read, or -1 on error.
 */
int mini_fread(void *buffer, int size_element, int number_element,
               MYFILE *file);

/*
 * mini_fwrite - Writes data from a buffer to a MYFILE object.
 *
 * @buffer: Source buffer containing data to write.
 * @size_element: Size of each element to be written.
 * @number_element: Number of elements to be written.
 * @file: Pointer to the MYFILE object to which data will be written.
 *
 * Writes up to `number_element` elements of size `size_element` from the
 * provided buffer to the specified MYFILE object. Data is written from an
 * internal buffer, which is flushed when full.
 *
 * Returns: Number of elements successfully written, or -1 on error.
 */
int mini_fwrite(void *buffer, int size_element, int number_element,
                MYFILE *file);

/*
 * mini_fflush - Flushes the write buffer of a MYFILE object.
 *
 * @file: Pointer to the MYFILE object to flush.
 *
 * If there is any data in the write buffer, it is written to the file and the
 * buffer index is reset.
 *
 * Returns: Number of bytes written, or -1 on error.
 */
int mini_fflush(MYFILE *file);

/*
 * mini_fclose - Closes an open MYFILE.
 *
 * @file: Pointer to the MYFILE object to close.
 *
 * This function closes an open file, flushes any remaining write buffers,
 * removes the file from the global list, and frees all associated memory.
 *
 * Returns: 42 on success, -1 on error.
 */
int mini_fclose(MYFILE *file);

/*
 * mini_fgetc - Reads a character from a MYFILE.
 *
 * @file: Pointer to the MYFILE object to read from.
 *
 * This function reads the next character from the read buffer of the specified
 * file. If the buffer is empty or exhausted, it reads more data from the file
 * descriptor.
 *
 * Returns: The read character (as an integer), or -1 if an error occurs.
 */
int mini_fgetc(MYFILE *file);

/*
 * mini_fputc - Writes a character to a MYFILE.
 *
 * @file: Pointer to the MYFILE object to write to.
 * @c: Character to write.
 *
 * This function writes a character to the write buffer of the specified MYFILE
 * object. When the buffer is full, it is flushed to the file.
 *
 * Returns: The written character converted to an integer, or -1 if an error
 * occurs.
 */
int mini_fputc(MYFILE *file, char c);

/*
 * mini_io_exit - Cleans up and closes all open files.
 *
 * This function closes all open files remaining in the global list of files.
 * It flushes any pending write buffers and releases associated memory.
 */
void mini_io_exit(void);

#endif // !MINI_LIB.H

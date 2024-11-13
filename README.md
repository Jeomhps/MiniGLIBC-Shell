# MiniGLIBC-Shell

## Answers to questions

### Question 5:
**Why should we initialize the buffer with `'\0'` before returning it?**

Initializing the buffer with `'\0'` ensures it starts in a clean state, improving program behavior and reducing unexpected behavior or bugs, especially when dealing with strings, as it prevents potential buffer overflow issues if a string is missing a null terminator.

### Question 6:
**What does the `free` function in C do? Does it truly release memory?**

`free` marks a memory block as available for reuse, but it does not necessarily return the memory to the operating system; it typically just changes the status of the block so it can be reused for future allocations by the same program.

### Question 17:
**What happens if we try to print a string without a newline using our custom functions?**

If a string without a newline is printed, nothing is displayed because output occurs only when a newline is encountered. To fix this, buffers need to be flushed when the program exits, using functions like `mini_exit` to ensure all data is outputted.

### Question 21:
**What happens if the number of characters entered equals the buffer size? Propose and implement a solution.**

If the number of characters entered equals or exceeds the buffer size, excess characters remain in the input stream and may be displayed later or cause issues. To fix this, you can read and discard remaining characters until a newline is encountered.

### Question 31:
**What happens if the program terminates when the write buffer isn’t full?**

If the program ends without a full write buffer, the data may not be written to the file. To prevent this, flush all open file buffers during `mini_exit` by maintaining a list of open files and ensuring they are properly flushed before program termination.

## References :

### mini_calloc (Exercise 4) :

- https://www.youtube.com/watch?v=NDKArv9WAlQ
- https://youtu.be/XV5sRaSVtXQ?t=179
- https://www.youtube.com/watch?v=HUXS5mo738w (Relevant information at 2:32, ((void *)- 1) )
- https://www.youtube.com/watch?v=vEXRpiI4Dhk

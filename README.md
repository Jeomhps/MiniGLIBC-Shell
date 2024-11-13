# MiniGLIBC-Shell

## Introduction:

This project involves the development of a minimalist implementation of the GNU C Library (glibc) functions, created using low-level system calls and with a strong emphasis on proper error handling. By building essential functions such as memory allocation, string manipulation, and input/output operations, this project provides a deep understanding of how core functionalities work at the system level. The minimalist glibc is then leveraged to construct a basic shell environment with custom utility functions like `mini_cat` and others, demonstrating extended usage of the created library. This hands-on approach helps to illuminate the inner workings of the `/bin/bash` executable, offering insights into how memory management, input/output operations, and other fundamental behaviors operate in Unix-like systems.

## Implementation:

The implementation of this project follows a lab-driven approach, with foundational elements such as using a linked list to track allocated memory, or open files, are provided in the lab instructions. Similar to the glibc, each function acts as a "safe" wrapper for system calls; errors are typically signaled by returning -1, with `errno` set to a relevant value. This strategy simplifies error detection and troubleshooting, especially when combined with `mini_perror` to display both a descriptive error message and the associated `errno` value, making it easier to search for error causes online.

The overall codebase adheres to the KISS (Keep It Stupid Simple) principle. While showcasing advanced coding techniques and concise C code can be impressive, my priority has been to maintain a high level of readability. This ensures that not only others but also I can easily comprehend, debug, and modify the code in the future. This straightforward design philosophy helps to demonstrate core concepts clearly, such as memory management and I/O handling, while building a functional and educational custom shell environment.

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

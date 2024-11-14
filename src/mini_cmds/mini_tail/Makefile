#Makefile

CC = gcc
CFLAGS = -g -W -Wall 
OBJ = mini_tail.c ../../mini_glibc/mini_io.c ../../mini_glibc/mini_string.c \
	../../mini_glibc/mini_memory.c ../../mini_glibc/mini_lib.h 

spin_app: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o mini_tail

clean :
	rm -f mini_tail

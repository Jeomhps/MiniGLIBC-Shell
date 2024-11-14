#Makefile

CC = gcc
CFLAGS = -g -W -Wall 
OBJ = wc.c ../../mini_glibc/mini_io.c ../../mini_glibc/mini_string.c \
	../../mini_glibc/mini_memory.c ../../mini_glibc/mini_lib.h 

spin_app: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o wc 

clean :
	rm -f wc

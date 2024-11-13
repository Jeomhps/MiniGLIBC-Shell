#Makefile

CC = gcc
CFLAGS = -g -W -Wall -fsanitize=address 
OBJ = mini_string.o mini_memory.o main.o mini_io.o

spin_app: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o app

mini_string.o: mini_string.c mini_lib.h
mini_memory.o: mini_memory.c mini_lib.h
mini_io.o: mini_io.c mini_lib.h
main.o: main.c mini_lib.h

clean :
	rm -f $(OBJ) app

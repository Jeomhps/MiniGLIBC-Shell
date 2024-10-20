#Makefile

CC = gcc
CFLAGS = -g -W -Wall
OBJ = mini_string.o mini_memory.o main.o

spin_app: $(OBJ)
	$(CC) $(OBJ) -o app

mini_string.o: mini_string.c mini_lib.h
mini_memory.o: mini_memory.c mini_lib.h
main.o: main.c mini_lib.h

clean :
	rm -f $(OBJ) app

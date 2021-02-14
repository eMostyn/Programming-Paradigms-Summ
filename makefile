CC=gcc
CFLAGS=-Wall -ggdb3 -Wextra -pedantic -std=c11

main: main.o connect4.o
	$(CC) $(CFLAGS) main.o connect4.o -o program

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

connect4.o: connect4.c connect4.h
	$(CC) -c $(CFLAGS) connect4.c

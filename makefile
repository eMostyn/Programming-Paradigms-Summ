CC=gcc
CFLAGS=-Wall -g -Wextra -pedantic -std=c11

main: connect4.o
	$(CC) $(CFLAGS) connect4.o  -o main

connect4.o: connect4.c connect4.h
	$(CC) -c $(CFLAGS) connect4.c

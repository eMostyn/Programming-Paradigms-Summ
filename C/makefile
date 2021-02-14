CC=gcc
CFLAGS=-Wall -g -Wextra -pedantic -std=c11

main: sort.o
	$(CC) $(CFLAGS) sort.o -o sort

sort.o: sort.c
	$(CC) -c $(CFLAGS) sort.c

CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11
main: maths_prog
maths_prog: libmaths.so maths_prog.o
	$(CC) $(CFLAGS) maths_prog.o  -L. -lmaths -o maths_prog

libmaths.so: add.o subtract.o
	$(CC) $(CFLAGS)  -shared add.o subtract.o  -o libmaths.so  -lm

maths_prog.o:
	$(CC) -c $(CFLAGS) -fPIC maths_prog.c


add.o: add.c add.h
	$(CC) -c $(CFLAGS) -fPIC add.c

subtract.o: subtract.c subtract.h
	$(CC) -c $(CFLAGS) -fPIC subtract.c

clean:
	rm add.o subtract.o maths_prog.o maths_prog libmaths.so

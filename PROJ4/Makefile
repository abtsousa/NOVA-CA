CC=gcc
CFLAGS=-g
all: main

main: main.o searchStrings.o
	gcc --static -g -o main main.o searchStrings.o

main.o:main.c
	gcc -g -c -o main.o main.c

searchStrings.o: searchStrings.s
	as -g -o searchStrings.o searchStrings.s

clean:
	rm -f *.o main

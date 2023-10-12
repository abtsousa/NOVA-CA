CC=gcc
CFLAGS=-g
all: main
main: main.o mf.o
	$(CC) $(CFLAGS) -static -o main *.o
main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c
mf.o: mf.s
	as -gstabs -o mf.o mf.s

clean:
	rm -f *.o  main

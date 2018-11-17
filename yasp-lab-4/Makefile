CC=gcc
CFLAGS=-g -c
run: main
	./main

main: main.o
	$(CC) -o main main.o
main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o
clean:
	rm -f main main.o

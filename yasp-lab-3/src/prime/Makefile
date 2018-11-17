CC=gcc
CFLAGS=-Wextra -g -c

run: main
	./main

main: main.o prime_checker.o
	$(CC) -o main main.o prime_checker.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

prime_checker.o: $(ARGS)
	$(CC) $(CFLAGS) $(ARGS) -o prime_checker.o

clean:
	rm -f main main.o
	rm -f prime_checker.o

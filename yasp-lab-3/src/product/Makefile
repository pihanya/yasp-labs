CC=gcc
CFLAGS=-g -c

run: main
	./main

main: main.o
	$(CC) -o main main.o cross_product.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

cross_product.o: cross_product.c
	$(CC) $(CFLAGS) cross_product.c -o cross_product.o

clean:
	rm -f main main.o
	rm -f cross_product cross_product.o

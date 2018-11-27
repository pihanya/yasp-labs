CC=gcc
CFLAGS=-Wall -Wextra -g -c

run: main
	./main

main: main.o
	$(CC) -o main main.o
main.o: main.c
	$(CC) $(CFLAGS) main.c high_order.c llist.c -o main.o
high_order.o:
    $(CC $(CFLAGS) high_order.c -o high_order.o

llist.o:
    $(CC $(CFLAGS) llist.c -o llist.o

clean:
	rm -f main main.o

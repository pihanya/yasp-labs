CC = gcc
C_FLAGS = -Wextra

WORKING_DIR = $(HOME)/JYOTI

BASICOBJS = prime.o scalar_product.o
OBJS = ./src

SCALAR_BIN=scalar
PRIME_BIN=prime

#OLDEST_FILE=find ./src -type f -printf '%T+ %p\n' | sort | head -n 1

scalar:

./src/%.o: %.cpp
	$(CC) $(C_FLAGS) -o $(SCALAR_BIN) -o $@ $<

prime:
	gcc -o $(PRIME_BIN) ./src/prime.c

clean:
	rm -rf $(SCALAR_BIN) $(PRIME_BIN)

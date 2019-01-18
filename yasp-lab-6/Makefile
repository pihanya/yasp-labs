CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.c alloc.c alloc_debug.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lab6

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

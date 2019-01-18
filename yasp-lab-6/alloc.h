#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define HEAP_START ((void*) 0x04040000)

typedef struct chunk_head chunk_head_t;
struct chunk_head {
    chunk_head_t *next;
    size_t capacity;
    bool is_free;
};

#define CHUNK_INIT_SIZE (1 * sysconf(_SC_PAGESIZE))

void *heap_init();

#define CHUNK_ALIGN 8

#define CHUNK_MIN_SIZE (sizeof(chunk_head_t) + CHUNK_ALIGN)

void *heap_alloc(size_t requested_size);

void heap_free(void *ptr);

#endif
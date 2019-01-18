#include <stdio.h>

#include "alloc.h"
#include "alloc_debug.h"

void test_empty_heap(chunk_head_t const *const heap_start) {
    puts("--- empty heap:");
    heap_full_dump(stdout, heap_start, 16);
}

void test_usual_heap(chunk_head_t const *const heap_start) {
    char *const p1 = heap_alloc(4096);
    for (size_t i = 0; i < 4096; i++) {
        p1[i] = (char) (i + 1);
    }
    printf("p1 = %p = heap_alloc(4096):\n", (void *) p1);
    heap_full_dump(stdout, heap_start, 16);

    char *const p2 = heap_alloc(64);
    for (size_t i = 0; i < 64; i++) {
        p2[i] = (char) (64 - i);
    }
    printf("--- p2 = %p = heap_alloc(64):\n", (void *) p2);
    heap_full_dump(stdout, heap_start, 16);

    heap_free(p1);
    puts("--- heap_free(p1)");
    heap_full_dump(stdout, heap_start, 0);

    heap_free(p2);
    puts("--- heap_free(p2)");
    heap_full_dump(stdout, heap_start, 0);
}

void test_large_heap(chunk_head_t const *const heap_start) {
    char *p3 = heap_alloc(4 * 1024 * 1024);
    printf("--- p3 = %p = heap_alloc(4 * 1024 * 1024)\n", (void *) p3);
    heap_full_dump(stdout, heap_start, 0);

    heap_free(p3);
    puts("--- heap_free(p3)");
    heap_full_dump(stdout, heap_start, 0);
}

int main(int argc, char **argv) {
    chunk_head_t const *const heap_start = heap_init();

    test_empty_heap(heap_start);

    test_usual_heap(heap_start);

    test_large_heap(heap_start);

    return 0;
}
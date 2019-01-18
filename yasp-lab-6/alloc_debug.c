#include "alloc_debug.h"

void heap_dump_chunk(FILE *const out, chunk_head_t const *const ptr, size_t const chunk_content_bytes_printed) {
  fprintf(out, "[%p] { next: %p, capacity: %zu, is_free: %s }",
          (void *) ptr, (void *) ptr->next, ptr->capacity, ptr->is_free ? "true" : "false");

  char const *const contents = (char *) (ptr + 1);

  for (size_t i = 0; i < chunk_content_bytes_printed; i++) {
    if (i % 16 == 0) {
      fprintf(out, "\n[%p]", (void *) (contents + i));
    }

    fprintf(out, " %02hhx", contents[i]);
  }

  if (chunk_content_bytes_printed > 0 && chunk_content_bytes_printed < ptr->capacity) {
    fprintf(out, " ... (%zu bytes omitted)", ptr->capacity - chunk_content_bytes_printed);
  }

  fputc('\n', out);
}

void heap_full_dump(FILE *const out, chunk_head_t const *const heap_start, size_t const chunk_content_bytes_printed) {
  for (chunk_head_t const *chunk = heap_start; chunk != NULL; chunk = chunk->next) {
    heap_dump_chunk(out, chunk, chunk_content_bytes_printed);
  }
}
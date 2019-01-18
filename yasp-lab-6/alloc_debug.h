#ifndef ALLOC_DEBUG_H
#define ALLOC_DEBUG_H

#include "alloc.h"
#include "stdio.h"

void heap_dump_chunk(FILE *out, chunk_head_t const *ptr, size_t chunk_content_bytes_printed);

void heap_full_dump(FILE *out, chunk_head_t const *heap_start, size_t chunk_content_bytes_printed);

#endif
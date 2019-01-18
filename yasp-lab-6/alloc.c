#include "alloc.h"

static void *const get_usable_area(chunk_head_t *const chunk) { return chunk + 1; }

static void *const get_chunk_end(chunk_head_t *const chunk) {
  return (void *) chunk + sizeof(chunk_head_t) + chunk->capacity;
}

static chunk_head_t *const get_chunk_head_by_usable_area(void *const usable_area) {
  return usable_area - sizeof(chunk_head_t);
}

static size_t get_size_of_usable_area(size_t const chunk_size) { return chunk_size - sizeof(chunk_head_t); }

void *heap_start;

chunk_head_t *const
construct_chunk_head(void *const chunk_ptr, chunk_head_t *const next, size_t const capacity, bool is_free) {
  chunk_head_t *chunk = chunk_ptr;
  chunk->next = next;
  chunk->capacity = capacity;
  chunk->is_free = is_free;
  return chunk;
}

void *heap_init() {
  heap_start = mmap(HEAP_START, (size_t) CHUNK_INIT_SIZE, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0);

  return (void *) construct_chunk_head(heap_start, NULL, get_size_of_usable_area((size_t) CHUNK_INIT_SIZE), true);
}

bool reserve_new_chunk(chunk_head_t *const last_chunk, size_t const requested_size) {
  void *const heap_end = get_chunk_end(last_chunk);
  size_t const chunk_size = requested_size + requested_size % sysconf(_SC_PAGESIZE);

  void *new_area = mmap(heap_end, chunk_size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0);
  if (new_area != MAP_FAILED && last_chunk->is_free) {
    last_chunk->capacity += chunk_size;
    return true;
  } else if (new_area == MAP_FAILED) {
    new_area = mmap(NULL, chunk_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (new_area == MAP_FAILED) {
      return false;
    }
  }

  chunk_head_t *const new_chunk_head =
      construct_chunk_head(new_area, NULL, get_size_of_usable_area(chunk_size), true);
  last_chunk->next = new_chunk_head;

  return true;
}

void merge_succeeding_free_chunks(chunk_head_t *const chunk) {
  while ((char *) chunk->next == get_usable_area(chunk) + chunk->capacity && chunk->next->is_free) {
    chunk->capacity += chunk->next->capacity + sizeof(chunk_head_t);
    chunk->next = chunk->next->next;
  }
}

chunk_head_t *get_free_chunk(size_t requested_size) {
  chunk_head_t *chunk = (chunk_head_t *) heap_start;
  while (true) {
    if (chunk->is_free) {
      merge_succeeding_free_chunks(chunk);
      if (chunk->capacity >= requested_size) {
        return chunk;
      }
    }

    if (chunk->next == NULL) {
      if (!reserve_new_chunk(chunk, requested_size)) {
        return NULL;
      }
    } else {
      chunk = chunk->next;
    }
  }
}

void *heap_alloc(size_t requested_size) {
  if (requested_size % CHUNK_ALIGN != 0) {
    requested_size += CHUNK_ALIGN - (requested_size % CHUNK_ALIGN);
  }

  chunk_head_t *chunk = get_free_chunk(requested_size);
  if (chunk == NULL) {
    return NULL;
  }

  chunk->is_free = false;

  size_t const remaining_capacity = chunk->capacity - requested_size;
  if (remaining_capacity < CHUNK_MIN_SIZE) {
    return get_usable_area(chunk);
  } else {
    chunk->capacity = requested_size;
    char *const chunk_end = get_chunk_end(chunk);

    construct_chunk_head(chunk_end, chunk->next, get_size_of_usable_area(remaining_capacity), true);

    chunk->next = (chunk_head_t *) chunk_end;

    return get_usable_area(chunk);
  }
}

void heap_free(void *const ptr) {
  chunk_head_t *const ptr_chnk = get_chunk_head_by_usable_area(ptr);
  ptr_chnk->is_free = true;
  merge_succeeding_free_chunks(ptr_chnk);
}
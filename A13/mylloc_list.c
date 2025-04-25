/**
 * Name: Reagan Buvens
 * Date: 04/25/2025
 * Description: Implements malloc and free using a free list, such that
 * previously allocated memory space may be reused after being freed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (size == 0) {
    return NULL;
  }
  struct chunk *next = flist;
  struct chunk *prev = NULL;

  while (next != NULL) {
    if (next->size >= size) {
      next->used = size;
      if (prev != NULL) {
        prev->next = next->next;
      }
      else {
        flist = next->next;
      }
      return (void*)(next + 1);
    }
    else {
      prev = next;
      next = next->next;
    }
  }

  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) - 1) {
    return NULL;
  }
  else {
    struct chunk *cnk = (struct chunk*) memory;
    cnk->size = size;
    cnk->used = size;
    return (void *)(cnk + 1);
  }
}

void free(void *memory) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (memory != NULL) {
    struct chunk *cnk = (struct chunk*) ((struct chunk*)memory - 1);
    cnk->next = flist;
    cnk->used = 0;
    flist = cnk;
  }
  return;
}

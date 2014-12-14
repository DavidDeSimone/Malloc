#include "block.h"
#include "mymalloc.h"

char* heap_init(char *heap) {
  /* Initalize the heap initally as a empty block  */
  struct block add;
  add.next = NULL;
  add.prev = NULL;

  add.addr = heap;
  add.size = HEAP_SIZE - sizeof(struct block);
  add.open = TRUE;

  /* Set the first block on the simulated heap */
  memcpy(heap, &add, sizeof(struct block));

  return heap;
}


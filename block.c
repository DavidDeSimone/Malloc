#include "block.h"

char* heap_init(char heap[HEAP_SIZE]) {
  /* Initalize the heap initally as a empty block  */
  struct block add;
  add.next = NULL;
  add.prev = NULL;

  /* Offset the data pointer from the header block */
  add.addr = heap + sizeof(struct block);

  /* Set the inital size to be the size of the heap minus
   * the data header
   */
  add.size = HEAP_SIZE - sizeof(struct block);
  add.open = TRUE;

  /* Set the first block on the simulated heap */
  memcpy(heap, &add, sizeof(struct block));

  return heap;
}


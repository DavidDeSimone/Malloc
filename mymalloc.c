#include "mymalloc.h"

/* Character array used to simulate the heap on .data */
/* Heap size defined in mymalloc.h */
char myheap[HEAP_SIZE];

void* mymalloc(size_t size, char *FILE, char *LINE) {
  static uint8_t initalized = FALSE;
  
  if(!initalized) {
    heap_init(&myheap);
    initalized = TRUE;
  }

  /* If the user asks for more memory than can fit on the
   * heap...
   */
  if(size > HEAP_SIZE) {
    printerr("Out of Heapspace", FILE, LINE);
    return NULL;
  }

  block *front = (block *)myheap;

  /* Iterate over memory blocks, find free blocks */
  block *min = NULL;
  while(front != NULL) {
    if(front->open == TRUE && front->size > size) {
      
      /* Set the minimum if we find a smaller open block */
      if(!min) {
	min = front;
      } else {
	if(front->size < min->size) {
	  min = front;
	}
      }

    }

    front = front->next;
  }

  /* If we find no open block that fits our size needs */
  if(!min) {
    printerr("No open block found for given memory request", FILE, LINE);
    return NULL;
  }

  /* If our minimum block is the perfect size.. */
  if(min->size == size) {
    min->open = FALSE;
    //TODO make sure this is accounting for the block size in the pointer
    return &min + sizeof(struct block);
  }

  //If its too big, resize the block and add a new header
  if(min->size > size) {

    /* If we have enough room to add another header  */
    if(min->size > (size - sizeof(struct block))) {
      
      /* If we have room for a header AND data */
      if(size - sizeof(struct block) > 0) {
	/* Initalize block header to be added */
	struct block add;
 
	/* Insert new block after current item */
	add.next = min->next;
	add.prev = min;

	/* Set the address of the block to be the current address plus the offset
	 * of size we are allocating plus the size of the header
	 */
	add.addr = &min + size + sizeof(block);

	/* The size of the new block will be the current size minus the allocated chunk minus the size of the 
	 * new header
	 */
	add.size = min->size - size - sizeof(block);
	add.open = TRUE;

	/* Copy the new header onto the heap */
	memcpy(min + size, &add, sizeof(block));

	/* Set the current item to point to the new header */
	min->next = (block *)min + size;
	min->open = FALSE;

	return min->addr;

      } else {
	/* Else we have the case where we only have enough room to add a header and no data */

      }



    }


  }




  //TODO Make sure you account for the header size on the heap (since the headers will be in the heap)


  return NULL;
}

void myfree(void *ptr, char *FILE, char *LINE) {



}


void printerr(char *msg, char *FILE, char *LINE) {
  printf("Error in %s at %s: %s\n", FILE, LINE, msg);
}

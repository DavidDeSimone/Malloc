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

  block *front = (block *)myheap[0];
  //Iterate over memory blocks
  //Find free blocks
  
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
    printerr("Not enough heap space", FILE, LINE);
    return NULL;
  }

   
  //If its too big, resize the block and add a new header

  //TODO Make sure you account for the header size on the heap (since the headers will be in the heap)


  return NULL;
}

void myfree(void *ptr, char *FILE, char *LINE) {



}


void printerr(char *msg, char *FILE, char *LINE) {
  printf("Error in %s at %s: %s\n", FILE, LINE, msg);
}
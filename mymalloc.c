#include "mymalloc.h"
#include "block.h"

/* Character array used to simulate the heap on .data */
/* Heap size defined in mymalloc.h */
char myheap[HEAP_SIZE];

/* Global variable used to denote if the heap has been initalized */
static uint8_t initalized = FALSE;

void* mymalloc(size_t size, char *FILE, int LINE) {
  if(!initalized) {
    heap_init(myheap);
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
    if(front->open == TRUE && front->size >= size) {
      
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
    return min->addr;
  }

  //If its too big, resize the block and add a new header
  if(min->size > size) {

    /* If we have enough room to add another header  */
    if(min->size >= (size - sizeof(struct block))) {
      
      /* If we have room for a header AND data */
      if(size - sizeof(struct block) > 0) {
	/* Initalize block header to be added */
	struct block add;
 
	if(size < SMALL_ALLOCATION) {
	  /* Insert new block after current item */
	  add.next = min->next;
	  add.prev = min;

	  /* Set the address of the block to be the current address plus the offset
	   * of size we are allocating plus the size of the header
	   */
	  add.addr = (char *)min + size + sizeof(block);

	  /* The size of the new block will be the current size minus the allocated chunk minus the size of the 
	   * new header
	   */
	  add.size = (char *)min->size - size - sizeof(block);
	  add.open = TRUE;

	  /* Copy the new header onto the heap */
	  /* min must be casted as a char* to ensure we only move forward size bytes 
	     and not sizeof(block) * size bytes */
	  memcpy((char *)min + size, &add, sizeof(struct block));
	  
	  /* Set the current item to point to the new header */
	  min->next = (char *)min + size;
	  min->open = FALSE;
	  min->size = size;
	  
	  return min->addr;

	} else {
	  /* If our allocation amount is larger than
	   * SMALL_ALLOCATION, we allocate to the RIGHT side of the heap
	   */
	  add.prev = min;
	  add.next = min->next;

	  add.addr = min->addr + (min->size - size);
	  
	  add.size = size;
	  add.open = FALSE;

	  memcpy(min->addr + (min->size - size - sizeof(block)), &add, sizeof(block));

	  min->next = min->addr + min->size - size - sizeof(block);
	  min->open = TRUE;
	  min->size = min->size - size - sizeof(block);

	  return min->next->addr;
	}

      } else {
	/* Else we have the case where we only have enough room to add a header and no data */
	min->next = NULL;
	min->open = FALSE;
	
	return min->addr;
	
      }
    }

  } else {
    printerr("Not enough heap space", FILE, LINE);
    return NULL;
  }

  printerr("Fallthrough error", FILE, LINE);
  return NULL;
}

void myfree(void *ptr, char *FILE, int LINE) {
  if(!initalized) {
    printerr("Attempting to free unallocted pointer", FILE, LINE);
    return;
  }

  block *front = (block *)myheap;

  /* Look through allocated blocks */
  while(front != NULL) {

    /* If we find out address to free */
    if(front->addr == ptr) {
      if(front->open) {
	printerr("Error, attempting to free already free'd memory", FILE, LINE);
	return;
      }

      front->open = TRUE;
      /* Attempt to merge with right block if it's free */
      if(front->next != NULL && front->next->open == TRUE) {
	front->size += front->next->size;

	front->next = front->next->next;	
	if(front->next != NULL) {
	  front->next->prev = front;
	}

      }
      
      /* Attempt to merge with left block it it's free */
      if(front->prev != NULL && front->prev->open == TRUE) {
	front->prev->size += front->size;

	if(front->next != NULL) {
	  front->next->prev = front->prev;
	}
	front->prev->next = front->next;

      }

      /* Once memory is free'd, we can just return */
      return;
    }

    front = front->next;
  }

  /* If the requested block is not found, throw error */
  printerr("Error, attempting to free unalloacted pointer", FILE, LINE);

}

void printerr(char *msg, char *FILE, int LINE) {
  printf("Error in %s at line %d: %s\n", FILE, LINE, msg);
}

void leak_check() {
  int _def_lost = 0;
  int _blocks_lost = 0;
  
  if(!initalized) {
    /* Heap was never set, return silently */
    return;
  }


  block *front = (block *)myheap;

  while(front != NULL) {

    if(!front->open) {
      /* We have a memory leak! */
      printf("Memory leak detected @ %p, %d bytes definitly lost\n", front->addr, front->size);
      _def_lost += front->size;
      ++_blocks_lost;
    }

    front = front->next;
  }

  if(_def_lost > 0) {
    printf("Final Report, %d bytes of memory lost accross %d blocks\n", _def_lost, _blocks_lost); 
  }

}

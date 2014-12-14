#ifndef BLOCK_H
#define BLOCK_H

#define TRUE 1
#define FALSE 0

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct block {
  struct block *next;
  struct block *prev;

  void *addr;
  size_t size;
  uint8_t open;
};

typedef struct block block;

struct heap {
  char *front;
};

typedef struct heap heap;

/* Initalizes a heap object from a char[] simulating the 
 * heap 
 */
char* heap_init(char *heap);



#endif



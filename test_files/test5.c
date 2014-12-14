#include "mymalloc.h"
#include <stdio.h>

/* Fragmentation test, assumes heap of size 5000 bytes */
int main(int argc, char **args) {
  void *alloc = malloc( 100 );
  void *salloc = malloc( 100 );
  void *jalloc = malloc( 500 );
  void *dalloc = malloc( 2500 );
  void *kalloc = malloc( 1500 );

  printf("Allocated pointers at %p (100), %p (100), %p (500), %p (2500), %p (1500)\n", alloc, salloc, jalloc, dalloc, kalloc);

  free(alloc);
  free(salloc);

  printf("Free'd address (1) and (2) for 100 bytes each\n");

  void *zalloc = malloc ( 150 );
  printf("Allocated 150 bytes @ %p\n", zalloc);

  return 0;
}

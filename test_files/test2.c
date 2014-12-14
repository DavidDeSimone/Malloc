#include "mymalloc.h"
#include <stdio.h>

/* Attempt to allocate 2000 bytes in two rounds */
/* Then attempt to allocate over default 5000 byte heap limit */
int main(int argc, char **args) {
  void *alloc = malloc ( 1000 );
  void *salloc = malloc ( 1000 );
  
  printf("Allocated at %p and %p for 1000 bytes each\n", alloc, salloc);

  void *dalloc = malloc ( 10000 );
  
  printf("This allocation should have failed!\n");


  return 0;
}

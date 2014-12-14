#include "mymalloc.h"
#include <stdio.h>

/* Basic Test, malloc a variable half the size of the heap */
int main(int argc, char **args) {
  void *alloc = malloc( 2500 );
  printf("Allocation Sucessful at %p\n", alloc);

  return 0;
}

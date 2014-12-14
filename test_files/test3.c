#include "mymalloc.h"
#include <stdio.h>

/* Basic test of malloc and free */
int main(int argc, char **args) {
  void* ptr = malloc ( 1000 );
  free( ptr );

  printf("Memory allocated and free'd\n");

  return 0;
}

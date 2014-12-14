#include "mymalloc.h"
#include <stdio.h>

/* Allocates memory for 2 pointers, attempts to free same pointer twice */
int main(int argc, char **args) {
  void *ptr = malloc( 1000 );
  void *ptr2 = malloc ( 1000 );

  free( ptr2 );
  free( ptr2 );

  free( ptr );


  return 0;
}

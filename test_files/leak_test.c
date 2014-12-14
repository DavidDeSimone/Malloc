#include "mymalloc.c"
#include <stdio.h>
#include <stdlib.h>

/* Leak test for extra credit */
int main(int argc, char **args) {
  atexit(leak_check);

  void *ptr = malloc( 1000 );
  void *ptr2 = malloc( 250 );
  void *ptr3 = malloc( 1000 );

  free( ptr2 );


  return 0;
}

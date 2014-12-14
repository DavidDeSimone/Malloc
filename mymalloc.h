#ifndef MALLOC_H
#define MALLOC_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Defines the size of the simulated heap in bytes */
#define HEAP_SIZE 5000

/* Defines a "small allocation". The allocation rules state that
 * all allocation requests below SMALL_ALLOCATION are allocated
 * to the left side of the heap, while largers requests are
 * allocated to the right.
 */
#define SMALL_ALLOCATION 350

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

void* mymalloc(size_t size, char *FILE, int LINE);
void myfree(void *ptr, char *FILE, int LINE); 

/* Used to print error messages containing FILE and LINE in
 * formation
 */
void printerr(char *msg, char *FILE, int LINE);

/* Function called at program exit (via atexit()) to check for
 * memory leaks on the heap. 
 * Will print formatted message of the leak if found. 
 */
void leak_check();


#endif

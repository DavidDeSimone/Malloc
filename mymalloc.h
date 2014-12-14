#ifndef MALLOC_H
#define MALLOC_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "block.h"

/* Defines the size of the simulated heap in bytes */
#define HEAP_SIZE 5000

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) mymalloc( x, __FILE__, __LINE__ )

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

void* mymalloc(size_t size, char *FILE, char *LINE);
void myfree(void *ptr, char *FILE, char *LINE); 

/* Used to print error messages containing FILE and LINE in
 * formation
 */
void printerr(char *msg, char *FILE, char *LINE);


#endif

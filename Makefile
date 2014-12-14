CC = gcc
AR = ar rcs
CFLAGS = -g -Wall
LFLAGS = -I.
OUTPUT = malloc.a
OBJS = malloc.o block.o
TEST1 = test1
TEST2 = test2

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(AR) $(OUTPUT) $(OBJS)

malloc.o: mymalloc.c
	$(CC) $(CFLAGS) $(LFLAGS) -o malloc.o -c mymalloc.c

block.o: block.c
	$(CC) $(CLAGSS) $(LFLAGS) -o block.o -c block.c

clean:
	rm ./*.o ./*.a



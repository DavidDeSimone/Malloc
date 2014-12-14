CC = gcc
AR = ar rcs
CFLAGS = -g -Wall
LFLAGS = -I. -l:malloc.a
OUTPUT = malloc.a
OBJS = malloc.o block.o

TEST = mtest

TEST1 = test1
TEST2 = test2

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(AR) $(OUTPUT) $(OBJS)

malloc.o: mymalloc.c
	$(CC) $(CFLAGS) $(LFLAGS) -o malloc.o -c mymalloc.c

block.o: block.c
	$(CC) $(CLAGSS) $(LFLAGS) -o block.o -c block.c

$(TEST1): test1.c
	$(CC) $(CFLAGS) -o $(TEST) test1.c $(LFLAGS)

$(TEST2): test2.c
	$(CC) $(CFLAGS) -o $(TEST) test2.c $(LFLAGS)

clean:
	rm ./*.o ./*.a $(TEST)



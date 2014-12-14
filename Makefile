CC = gcc
AR = ar rcs
CFLAGS = -g -Wall
LFLAGS = -I. -l:malloc.a
OUTPUT = malloc.a
OBJS = malloc.o block.o

#Output test program to be run
TEST = mtest

#Basic test to malloc 2500 bytes
TEST1 = test1

#Test to malloc 2000 bytes across two calls and to attempt (and fail) to
#malloc 10000 bytes
TEST2 = test2

TEST3 = test3
TEST4 = test4

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(AR) $(OUTPUT) $(OBJS)

malloc.o: mymalloc.c
	$(CC) $(CFLAGS) $(LFLAGS) -o malloc.o -c mymalloc.c

block.o: block.c
	$(CC) $(CLAGSS) $(LFLAGS) -o block.o -c block.c

$(TEST1): test_files/test1.c
	$(CC) $(CFLAGS) -o $(TEST) test_files/test1.c $(LFLAGS)

$(TEST2): test_files/test2.c
	$(CC) $(CFLAGS) -o $(TEST) test_files/test2.c $(LFLAGS)

$(TEST3): test_files/test3.c
	$(CC) $(CFLAGS) -o $(TEST) test_files/test3.c $(LFLAGS)

$(TEST4): test_files/test4.c
	$(CC) $(CFLAGS) -o $(TEST) test_files/test4.c $(LFLAGS)

clean:
	rm ./*.o ./*.a $(TEST)



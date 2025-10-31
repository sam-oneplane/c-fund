
CC=gcc
CFLAGS=-g -Wall -std=c11
BINS = rand_alloc

all: $(BINS)

%alloc: %alloc.o mem_allocator.o
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o $(BINS)
	
# ./rand_alloc 2> mem_allocs.log

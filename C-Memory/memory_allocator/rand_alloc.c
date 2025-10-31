
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

const int MAX_OBJ = 100;
const int NUM_ITER = 5000;
const int MAX_SIZE = 200;
const int MIN_SIZE = 50;

struct allocation {
	void *block; // pointer to memory block on the heap
	bool isvalid;
};


void do_list_of_allocations() {

	struct allocation allocs[MAX_OBJ]; // on stack
	for(int i = 0; i < MAX_OBJ; i++)
		allocs[i].isvalid = false;
	
	for(int i = 0; i < NUM_ITER; i++) {
		int ridx = rand() % MAX_OBJ; // select rand idx
		size_t size = MIN_SIZE + (rand() % (MAX_SIZE - MIN_SIZE)); // select alloc size

		if(allocs[ridx].isvalid) {
			free(allocs[ridx].block);
			allocs[ridx].isvalid = false;
		}else {
			allocs[ridx].block = malloc(size);
			allocs[ridx].isvalid = true;
		}
	} // for
}


int main(int argc, char **argv) {

	srand(time(NULL)); // seed number for rand()
	do_list_of_allocations();
	return EXIT_SUCCESS;
}
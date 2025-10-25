#include "shared/shared_mem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 1) {
        printf("usage - %s [no args]\n", argv[0]);
        return -1;
    }

    // destroy memory block
    if (destroy_mem_block(FILENAME))
        printf("block associated to file %s is destroyed\n", FILENAME);
    else
        printf("block associated to file %s could not be destroyed\n", FILENAME);

    return 0;
}
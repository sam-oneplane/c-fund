#include "shared/shared_mem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

#define NUM_ITERATIONS 10

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("usage - %s [stuff to write]\n", argv[0]);
        return -1;
    }
    /*
    void *handle = dlopen("./libsharedmem.so", RTLD_LAZY);
    if( !handle ) {
        printf("error loading .so lib %s\n", dlerror());
        return 1;
    }
    */

    // reader start 1st just open dont create
    sem_t *sem_prod = sem_open(SEM_PROD_FNAME, 0);
    if(sem_prod == SEM_FAILED){
        printf("error opening sam_open/producer\n");
        exit(EXIT_FAILURE);
    }
    sem_t *sem_cons = sem_open(SEM_CONS_FNAME, 1);
    if(sem_cons == SEM_FAILED){
        printf("error opening sam_open/consumer\n");
        exit(EXIT_FAILURE);
    }


    char *block = attach_mem_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        printf("error : couldn't get block\n");
        return -1;
    }

    for (int i =0; i < NUM_ITERATIONS; i++) {
        sem_wait(sem_cons); // wait fot the consumer to inc semaphore
        // cpy the 1st arg into shared block of memory
        strncpy(block , argv[1], BLOCK_SIZE);
        printf("writing:  %s\n", argv[1]);
        sem_post(sem_prod); // signal finish prducing text
    }
    
    
    sem_close(sem_cons);
    sem_close(sem_prod);
    detach_mem_block(block);
    return 0 ;
}


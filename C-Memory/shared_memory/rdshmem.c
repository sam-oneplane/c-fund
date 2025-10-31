#include "shared/shared_mem.h"
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc != 1) {
        printf("usage no args\n");
        return -1;
    }

    sem_unlink(SEM_CONS_FNAME);
    sem_unlink(SEM_PROD_FNAME);

    sem_t *sem_prod = sem_open(SEM_PROD_FNAME, O_CREAT, 0644, 0);
    if(sem_prod == SEM_FAILED){
        printf("error opening sam_open/myproducer\n");
        exit(EXIT_FAILURE);
    }
    sem_t *sem_cons = sem_open(SEM_CONS_FNAME, O_CREAT, 0644, 1);
    if(sem_cons == SEM_FAILED){
        printf("error opening sam_open/myconsumer\n");
        exit(EXIT_FAILURE);
    }

    char *block = attach_mem_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        printf("error : couldn't get block\n");
        return -1;
    }

    // impl semaphore
    while(true) {
        sem_wait(sem_prod); // wait until wrshmem produces text dec sem
        if(strlen(block) > 0){
            printf("reading:  %s\n", block);
            bool done = (strcmp(block, "quit") == 0);
            block[0] = 0; // empty char block[]
            if (done) break;
        }
        sem_post(sem_cons); // finish consuming test inc sem
    }

    sem_close(sem_cons);
    sem_close(sem_prod);
    
    detach_mem_block(block);
    return 0 ;

}


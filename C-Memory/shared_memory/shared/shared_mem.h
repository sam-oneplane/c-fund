#ifndef SHARED_MEM_H
#define SHARED_MEM_H


#include <stdbool.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char *attach_mem_block(char *filename, int size);
bool detach_mem_block(char *block);
bool destroy_mem_block(char *filename);

#define BLOCK_SIZE 4096
#define FILENAME "wrshmem.c"
#define IPC_RESULT_ERR -1

#define SEM_PROD_FNAME "myproducer" 
#define SEM_CONS_FNAME "myconsumer"

#endif
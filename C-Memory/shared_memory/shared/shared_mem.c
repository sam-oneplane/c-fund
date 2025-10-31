#include "shared_mem.h"
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>

// private function
static int get_shared_block(char *filename, int size) {
    key_t key;
    key = ftok(filename, 0); // generate unique key (key_t) path combined with id number

    if(key == IPC_RESULT_ERR)
        return IPC_RESULT_ERR;
    // get or create a block of mem with given size 
    return shmget(key, size, 0644 | IPC_CREAT);
}

char *attach_mem_block(char *filename, int size) {
    int shared_blk_id = get_shared_block(filename, size);
    if(shared_blk_id == IPC_RESULT_ERR)
        return NULL;

    char *res;
    res = shmat(shared_blk_id, NULL, 0);
    if(res == (char *)IPC_RESULT_ERR)
        return NULL;
    
    return res;
}

bool detach_mem_block(char *block) {
    return (shmdt(block) != IPC_RESULT_ERR);
}

bool destroy_mem_block(char *filename) {
    int shared_blk_id  = get_shared_block(filename, 0);
    if(shared_blk_id == IPC_RESULT_ERR)
        return NULL;
    
    return (shmctl(shared_blk_id, IPC_RMID, NULL) != IPC_RESULT_ERR);
    
}
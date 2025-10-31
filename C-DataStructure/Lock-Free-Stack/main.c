#include "stack.h"
#include <threads.h>

// Compile : gcc -std=c11 -pthread  main.c -o main -latomic

#define NODES 3
#define THREADS 20

_Atomic lfstack_t top = {0, NULL};
_Atomic __uint128_t dat = 0;

int push(void *input) {
    
    lfstack_push(&top, &dat);
    thrd_sleep(&(struct timespec){.tv_sec=1}, NULL);
    
    return 0;
}

int pop(void *input) {
    
    int result;
    result = lfstack_pop(&top);
    if(result == -1)
        printf("the stack is empty\n");
    thrd_sleep(&(struct timespec){.tv_sec=1}, NULL);
    
    return 0;
}

int main() {
    thrd_t tid[THREADS];
    for(int i=0; i<THREADS; i+=2) {
        thrd_create(&tid[i],push,NULL); 
        thrd_create(&tid[i+1],pop,NULL);
    }  
    
    for(int i=0; i<THREADS; i++)
        thrd_join(tid[i],NULL);  

    return 0;
}

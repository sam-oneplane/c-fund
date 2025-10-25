#include "stack.h"
#include <pthread.h>

// Compile : gcc -std=c11 -pthread  main.c -o main -latomic

_Atomic lfstack_t top = {0, NULL};
void *push(void *input) {
    for(__uint128_t i=0; i<1000; i++)    {
        lfstack_push(&top, i);
        printf("push %llx\n",(unsigned long long)i);
    }    
    pthread_exit(NULL);
}

void *pop(void *input) {
    for(__uint128_t i=0; i<1000;)  {
        int result;
        result = lfstack_pop(&top);
        if(result == -1)
            printf("the stack is empty\n");
        else {
            i++;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[200];
    for(int i=0; i<100; i++)
        pthread_create(&tid[i],NULL,push,NULL);
    for(int i=100; i<200; i++)
        pthread_create(&tid[i],NULL,pop,NULL);
    for(int i=0; i<200; i++)
        pthread_join(tid[i],NULL);  
    return 0;
}

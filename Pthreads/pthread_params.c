#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define ARRAY_SIZE 4
// global vars 
 
int primes[ARRAY_SIZE] = {7, 9, 13, 17};
int res_buff[ARRAY_SIZE] = {0,0,0,0};

typedef struct Params param_obj;
struct Params {
    int index;
    int prime;
};


void *rooldice(void *arg) {
    sleep(1);
    int value = rand() % (*(param_obj *)arg).prime + 1;
    int index = (*(param_obj *)arg).index;
    // alloc return value
    res_buff[index] = value;
    free(arg);
    printf(" res  index %d with result:  %d\n", index,value);
    pthread_exit(0); //replace return
}


int main(int argc, char **argv) {

    pthread_t pth[ARRAY_SIZE];
    srand(time(NULL));

    size_t len = sizeof(pth) / sizeof(pth[0]);
    
    for (size_t i = 0 ; i < len ; i++) {
        param_obj *gen = malloc(sizeof(param_obj));
        (*gen).prime = primes[(int)i];
        (*gen).index = i;
        if (pthread_create((pth + i), NULL, &rooldice, gen) != 0) {
            return (int)i;
        }

    }

    for (size_t i = 0 ; i < len ; i++) {
        printf("exit main thread\n");
        pthread_exit(0); // exit main thread keep process alive for child threads
        pthread_join(pth[i], NULL);
    }
    
    printf("\n");
    return 0;
}
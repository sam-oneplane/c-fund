
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

#define PTHREADS 2
#define PRODUCE 5
#define CONSUME 16
// global vars 
int gas = 0 ; 
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *produce(void *args){
    for(int i=0; i<PRODUCE; i++) {
        pthread_mutex_lock(&mu);
        gas+=PRODUCE;
        printf("gas production: %d\n", gas);
        pthread_mutex_unlock(&mu);
        pthread_cond_signal(&cond);
        sleep(1);
    }
}

void *consume(void *args){
    pthread_mutex_lock(&mu);
    while(gas < CONSUME){
        printf("below gas th, whating....\n");
        /*
            wait for cond_signal and check gas, if false:
            1. unlock_mutex
            2. wait for cond_signal
            3. lock the mutex
        */
        pthread_cond_wait(&cond, &mu); //
    }
    gas-=CONSUME;
    printf("gas consume: %d\n", gas);
    pthread_mutex_unlock(&mu);
}

int main(int argc, char **argv) {

    pthread_t pth[PTHREADS];
    //pthread_mutex_init(&mu, NULL);
    //pthread_cond_init(&cond, NULL);

    for (int i=0 ; i < PTHREADS; i++){
        if (i == 0){
            if(pthread_create((pth+i), NULL, &produce, NULL) != 0) {
                perror("failed to create thread\n");
                return -1;
            }
        }else{
            if(pthread_create((pth+i), NULL, &consume, NULL) != 0) {
                perror("failed to create thread\n");
                return -1;
            }
        }
    }
    for (int i=0 ; i < PTHREADS; i++){
         if (pthread_join(pth[i], NULL) != 0) {
            perror("failed to join thread\n");
            return -1;
         }
    }
    //pthread_mutex_destroy(&mu);
    //pthread_cond_destroy(&cond);
    return 0;

}

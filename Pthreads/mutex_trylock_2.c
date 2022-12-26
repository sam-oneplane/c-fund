#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

#define THRAEDS 10
#define MOD_DEMAND 15
#define GAS_SOURCE 4

// global vars 
int gas[GAS_SOURCE] = {100, 100, 100, 100} ;  // multple shared memory/global-sources
pthread_mutex_t mu[GAS_SOURCE];


// race condition

void *foo() {
    int demand = rand() % MOD_DEMAND;
    printf("demand  : %d\n", demand);
    for (int i = 0 ; i < GAS_SOURCE ; i++) {
        //mutex tries to lock (trylock) if no success it's moves on
        if (pthread_mutex_trylock(&mu[i]) == 0){
            
            if((gas[i] - demand) > 0) {
                gas[i] -= demand;
                usleep(500000);
                printf("gas remained on pump %d is: %d\n",i, gas[i]);
            }
            else{
                printf("gas is missing from pipe %d\n", i);
            }
            pthread_mutex_unlock(&mu[i]);
            break;  // after unlocking mutex
        }else{
            if (i == (GAS_SOURCE -1)) {
                printf("sleep and reset in 300ms\n");
                usleep(300000);
                i = 0 ;
            }
        }
    }   
       
}



int main(int argc, char **argv) {

    pthread_t pth[THRAEDS];
    for(int i = 0 ; i< GAS_SOURCE ; i++){
        pthread_mutex_init(&mu[i], NULL);
    }

    size_t pthreads = sizeof(pth) / sizeof(pth[0]);
    printf("threads : %d\n", (int)pthreads);

    for(size_t i=0 ; i<pthreads; i++){
        if(pthread_create((pth+i), NULL, &foo, NULL) != 0) {
            perror("failed to create thread\n");
            return -1;
        } 
    }
    for(size_t i=0 ; i<pthreads; i++){
        pthread_join(pth[i], NULL);
    }
    for(int i = 0 ; i< GAS_SOURCE ; i++){
        pthread_mutex_destroy(&mu[i]);
    }
    return 0;
}

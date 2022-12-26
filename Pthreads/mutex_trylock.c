#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

#define ARRAY_LENGTH 4

// global vars 
int mails = 0 ; 
pthread_mutex_t mu;


// race condition

void *foo() {
    //mutex lock is panding on mutex trylock moves on
    if(pthread_mutex_trylock(&mu) == 0) { 
        sleep(1);
        mails++;
        printf("Got the lock %d\n", mails);
        pthread_mutex_unlock(&mu);
    }
    else {
        printf("busy with code %d\n", EBUSY);
    }
    
}



int main(int argc, char **argv) {

    pthread_t pth[ARRAY_LENGTH];
    pthread_mutex_init(&mu, NULL);

    size_t len = sizeof(pth) / sizeof(pth[0]);

    for(size_t i=0 ; i<len; i++){
        if(pthread_create((pth+i), NULL, &foo, NULL) != 0) {
            perror("failed to create thread\n");
            return -1;
        } 
    }
    for(size_t i=0 ; i<len; i++){
        pthread_join(pth[i], NULL);
    }
    
    pthread_mutex_destroy(&mu);
    printf("counter: %d\n", mails);
    return 0;
}

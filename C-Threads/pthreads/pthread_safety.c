#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // sleep()
#include <stdlib.h>
#include <stdint.h>


#define BIG 1000000000UL

uint32_t countr = 0;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;

void *count_to_big(void *arg) {
    for (uint32_t i = 0 ; i < BIG; i++) {
        pthread_mutex_lock(&mu);
        countr++;
        pthread_mutex_unlock(&mu);
    }
    return NULL;
}

int main() {

    pthread_t thd ;
    pthread_create(&thd, NULL, count_to_big, NULL);

    void *arg = 0;
    count_to_big(arg);
    pthread_join(thd, NULL);
    printf("done counting %d\n", countr);
}
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define THREADS 4

void *rool_dice(void *args) {
    sleep(1);
    int value = (rand() % 6) + 1;
    // alloc return value
    int *res = malloc(sizeof(int));
    *res = value;
    printf("dice show %d\n", *res);
    return (void *)res;
}


int main(int argc, char **argv) {

    pthread_t pthreads[THREADS];
    pthread_attr_t detach_t;

    // set pthread_attr
    pthread_attr_init(&detach_t);
    // set the state of the pthread attr to detached.
    pthread_attr_setdetachstate(&detach_t, PTHREAD_CREATE_DETACHED);
    int *res=0 ;

    size_t len = sizeof(pthreads) / sizeof(pthreads[0]);
    printf("%d\n", (int)len);
    for (size_t i = 0 ; i < len ; i++) {
        if (pthread_create((pthreads + i), &detach_t, &rool_dice, NULL) != 0) {
            perror("creattion of pthread has failed\n");
        }
    }


    pthread_attr_destroy(&detach_t);
    pthread_exit(0); // wait for all threads to complete 

}
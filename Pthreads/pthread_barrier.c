/*
    barrier for pthread whating 
    get the thd value for blocked threads
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<errno.h>
#include<sys/syscall.h>


#define PTHREADS_BARRIER 4
#define PTHREADS_T 10


pthread_barrier_t barrier;

void *foo(

) {
    // internal thread-id in linux os it is not the pthread_t unsigned-long type
    printf("%d\n", (pid_t)syscall(SYS_gettid)); 
    for(;;) {
        printf("Waiting to pass barrier....\n ");
        pthread_barrier_wait(&barrier);
        printf("Passed the barrier!!! \n");
        sleep(1);
    }
}

int main(int argc, char **argv) {

    pthread_t threads[PTHREADS_T]; // pthread pull
    pthread_barrier_init(&barrier, NULL, PTHREADS_BARRIER);

    for (int i=0 ; i < PTHREADS_T; i++){
        if (pthread_create(&threads[i], NULL, &foo, NULL) != 0) {
            perror("Failed with thread creation");
        }
        printf("%lu\n", threads[i]); // unsigned lond thread identifier
    }
    
    for (int i=0 ; i < PTHREADS_T; i++){
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed with thread join");
        }
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}





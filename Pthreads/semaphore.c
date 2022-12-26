#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<semaphore.h>


#define THREADS 3
#define SEM_QUEUE 1 // = 1 for binary semaphore ,  > 1  non binary
#define RAND_MOD 6

sem_t sem; // queueu of threads

void *routine(void *args) {
    printf("User (%d) wait to login\n", *(int *)args);
    sem_wait(&sem); // dec semaphore by 1 (consume)
    printf("User (%d) is logged in\n", *(int *)args);
    sleep(rand() % RAND_MOD + 1);
    printf("(%d) logged out\n", *(int *)args);
    sem_post(&sem); // inc semaphore by 1 (produce)
    free(args);
}



int main(int argc, char **argv) {

    pthread_t pthreads[THREADS];
    pthread_attr_t detach_t;
    sem_init(&sem, 0, SEM_QUEUE); // 0 for main process ;1 for init value of queue

    // set pthread_attr
    pthread_attr_init(&detach_t);
    // set the state of the pthread attr to detached.
    pthread_attr_setdetachstate(&detach_t, PTHREAD_CREATE_DETACHED);

    size_t len = sizeof(pthreads) / sizeof(pthreads[0]);
    printf("%d\n", (int)len);

    for (size_t i = 0 ; i < len ; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create((pthreads + i), &detach_t, &routine, arg) != 0) {
            perror("creattion of pthread has failed\n");
            return -1;
        }
    }


    pthread_attr_destroy(&detach_t);
    sem_destroy(&sem);
    pthread_exit(0); // wait for all threads to complete 



    return 0;
}



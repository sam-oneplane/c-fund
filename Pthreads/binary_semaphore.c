#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<semaphore.h>


#define THREADS 1
#define BIN_SEM 1 // = 1 for binary semaphore ,  > 1  non binary
#define RAND_MOD 2

sem_t sem; // queueu of threads
int *gaz; // dynamicly alloc gas

void *routine(void *args) {

    printf("(%d) gaz is fualing...\n", *gaz);
    sem_post(&sem); // inc semaphore by 1 (produce)
}



int main(int argc, char **argv) {

    pthread_t pthreads[THREADS];
    sem_init(&sem, 0, 0);

    size_t len = sizeof(pthreads) / sizeof(pthreads[0]);
    printf("%d\n", (int)len);
    gaz = (int *)malloc(sizeof(int));
    *gaz = 100;
    
    for (size_t i = 0 ; i < len ; i++) {
        
        if (pthread_create((pthreads + i), NULL, &routine, NULL) != 0) {
            perror("creattion of pthread has failed\n");
            return -1;
        }
    }

    sem_wait(&sem); // dec semaphore by 1 (consume)
    printf("free allocated gaz\n");
    free(gaz);
    
    for (size_t i = 0 ; i < len ; i++) {
       
        if (pthread_join(*(pthreads + i), NULL) != 0) {
            perror("creattion of pthread has failed\n");
            return -1;
        }
    }
    
    sem_destroy(&sem);

    return 0;
}



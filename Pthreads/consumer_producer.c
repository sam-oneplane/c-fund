#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<semaphore.h>
#include<math.h>

#define THREADS 2
#define BUFFER_SIZE 10

// 1. manage shared memory access (mutex)
// 2. ceack if buffer is full
// 3. check empty buffer

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
int buffer[BUFFER_SIZE];
int count = 0;

void *producer(void *args) {
    while(1){
        usleep(800000);  // producer is generating quickly then consumer
        sem_wait(&empty_slots);
        pthread_mutex_lock(&mu);
        buffer[count] = rand() % 100;
        count++;
        pthread_mutex_unlock(&mu);
        sem_post(&full_slots);
    }
}

void *consumer(void *args) {
    while(1) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&mu);
        // consume
        printf("count :%d with value %d\n",count-1, buffer[count-1]);
        count--;
        pthread_mutex_unlock(&mu);
        sem_post(&empty_slots);
        sleep(1);
    }
}

int main(int argc, char **argv) {

    pthread_t pthreads[THREADS];
    pthread_attr_t detach_t;
    sem_init(&empty_slots, 0, BUFFER_SIZE); // 0 for main process ;1 for init value of queue
    sem_init(&full_slots, 0, 0); // 0 for main process ;1 for init value of queue
    // set pthread_attr
    pthread_attr_init(&detach_t);
    // set the state of the pthread attr to detached.
    pthread_attr_setdetachstate(&detach_t, PTHREAD_CREATE_DETACHED);

    size_t len = sizeof(pthreads) / sizeof(pthreads[0]);
    printf("%d\n", (int)len);

    for (size_t i = 0 ; i < len ; i++) {
        //int *arg = malloc(sizeof(int));
        if((int)i < floor(len/2)) {
        
            if (pthread_create((pthreads + i), &detach_t, &producer, NULL) != 0) {
                perror("creattion of pthread has failed\n");
                return -1;
            }
        }else {
            if (pthread_create((pthreads + i), &detach_t, &consumer, NULL) != 0) {
                perror("creattion of pthread has failed\n");
                return -1;
            }
        }
    }


    pthread_attr_destroy(&detach_t);
    sem_destroy(&full_slots);
    sem_destroy(&empty_slots);
    pthread_exit(0); // wait for all threads to complete 

}



#include "thread_pool.h"
 

task_t task_queue[QUEUE];
pthread_mutex_t mu ;
pthread_cond_t cond;


void execute_task(task_t *task) {
    int res = task->x + task->y;
    printf("task result : %d\n", res);
}


void submit_task(task_t task, int *task_count) {
    // lock unlock shared task queue
    pthread_mutex_lock(&mu);
    task_queue[(*task_count)++] = task;
    pthread_mutex_unlock(&mu);
    pthread_cond_signal(&cond); //signal to threads when submit task
}


void *start_thread(void *args) {
    task_t task;
    int task_count, task_flag;
    while(1) {
        task_count = *(int *)args;
        task_flag = 0 ;
        pthread_mutex_lock(&mu);
        // wait for condition var to mutex lock thread
        while(task_count == 0) {
            pthread_cond_wait(&cond, &mu);
        }
        task = task_queue[0]; // take the first task from queue 
        // shift task array to left
        for (unsigned int i = 0; i < task_count-1; i++) {
            task_queue[i] = task_queue[i+1];  
        }
        task_count--; 

        pthread_mutex_unlock(&mu);
        free(args);
        // execute_task is not part of mutex it is not shared resource
        execute_task(&task);
    }
}

void generate_threads(pthread_attr_t detach_t, pthread_t *pthread) {
    // set the state of the pthread attr to detached.
    pthread_attr_setdetachstate(&detach_t, PTHREAD_CREATE_DETACHED);

    for (int i=0 ; i < PTHREADS; i++){
        int *pool_c = (int *)malloc(sizeof(int));
        if(pthread_create((pthread+i), &detach_t, &start_thread, pool_c) != 0) {
            perror("failed to create thread\n");
        }
    }
}
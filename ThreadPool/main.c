#include "thread_pool.h"

task_t task_queue[QUEUE];
pthread_mutex_t mu ;
pthread_cond_t cond;
int task_count = 0;


void task_func(int x, int y) {
    printf("task sum %d, and prod %d\n", (x+y), (x*y));
}

void task_mod(int x, int y) {
    printf("task mod %d\n", (x%y));
}


void execute_task(task_t *task) {
    usleep(300000);
    task -> f(task->x, task->y);
}

// submit a task to queue from main thread and signal threads to execute
void submit_task(task_t task) {
    // lock unlock shared task queue
    pthread_mutex_lock(&mu);
    task_queue[task_count++] = task;
    pthread_mutex_unlock(&mu);
    pthread_cond_signal(&cond); //signal to threads when submit task
}

void *start_thread(void *args) {
    task_t task;
    while(1) {
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
        // execute_task is not part of mutex it is not shared resource
        execute_task(&task);
    }
}

// create the threads for the pool
void generate_threads(pthread_attr_t detach_t, pthread_t *pthread) {
    // set the state of the pthread attr to detached.
    pthread_attr_setdetachstate(&detach_t, PTHREAD_CREATE_DETACHED);

    for (int i=0 ; i < PTHREADS; i++){
        if(pthread_create((pthread+i), &detach_t, &start_thread, NULL) != 0) {
            perror("failed to create thread\n");
        }
    }
}

int main(int argc, char **argv) {

    pthread_t pthread[PTHREADS];
    pthread_attr_t detach_t;
    pthread_cond_init(&cond, NULL);

    pthread_mutex_init(&mu, NULL);
    // set pthread_attr
    pthread_attr_init(&detach_t);
    
    generate_threads(detach_t, pthread);
    // submit tasks
    srand(time(NULL)); //init rand generator
    for (unsigned int i=0; i< TASKS; i++) {
        task_t t = {
                .f = i%2 == 0 ? &task_func: &task_mod,
                .x = rand() % 100,
                .y = rand() % 100
        };
        submit_task(t);
    }

    pthread_attr_destroy(&detach_t);
    pthread_mutex_destroy(&mu);
    pthread_cond_destroy(&cond);
    pthread_exit(0); // wait for all threads to complete 
}
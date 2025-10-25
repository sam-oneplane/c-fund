#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

volatile bool done = false;
volatile bool sigarrive = false;

void *tfunc(void *arg) {
    uint32_t t = *((uint32_t *)arg);
    sleep(t);
    done=true;
    return NULL;
}

void handler(int sig) {
    if (sig == SIGINT)
        sigarrive = true;
}

int main() {

    pthread_t t1;
    uint32_t slp = 1;
    pthread_create(&t1, NULL, tfunc, &slp);
    printf("Waiting...\n");
    /* done needs to be volatile because if we use -O2 optimtzation
       this code will not work proparly in some OSs. 
       volatile tell the compilar to not optimize code relate to volatile varible
       because it can change by other thread or signal */
    while(!done){}
    printf("Ok moving on, waiting for ctrl-C to ctrate sigint\n");
    signal(SIGINT, handler);
    while (!sigarrive) {}
    printf("Done\n");
    return 0;
}

// clang -O2 -std=c11 volatille.c

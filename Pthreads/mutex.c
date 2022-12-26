#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define PTHREADS 4

// global vars 
int mails = 0 ; 
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER; // replace init


// race condition

void *goo() {
    for(int i = 0; i < 100000; i++){
        pthread_mutex_lock(&mu);
        mails++;         
        /*  the assembly code for mails++
            movl	mails(%rip), %eax
	        addl	$1, %eax
	        movl	%eax, mails(%rip)
	        addl	$1, -4(%rbp)
        */
       pthread_mutex_unlock(&mu);
    }
}



int main(int argc, char **argv) {

    pthread_t pth[PTHREADS];
    // pthread_mutex_init(&mu, NULL); replaced by initializer

    size_t len = sizeof(pth) / sizeof(pth[0]);
    printf("array size : %zu\n", len);

    for(size_t i=0 ; i<len; i++){
        if(pthread_create((pth+i), NULL, &goo, NULL) != 0) {
            perror("failed to create thread\n");
            return i;
        }
        printf("thread %zu started\n",  i);   
    }
    for(size_t i=0 
    ; i<len; i++){
        pthread_join(pth[i], NULL);
        printf("thread %zu ended\n",  i);
    }
    
    // pthread_mutex_destroy(&mu); // not mendatory
    printf("%d\n", mails);
    pthread_exit(0);
} 

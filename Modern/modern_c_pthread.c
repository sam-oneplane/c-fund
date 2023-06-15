#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdint.h>

_Atomic int a_count = 0;
int na_count = 0;
//
int lock_free_count = 0;


void *adding(void *input) {
    for(uint16_t i=0; i<10000; i++) {
        a_count++;
        na_count++;
    }
    pthread_exit(NULL);
}

void *counting(void *input) {
    int val;
    for(uint16_t i=0; i<10000; i++) {
        do {
            val = lock_free_count;
        //if the lock_count is 0(unlock), then set it to val+1(lock).
        }while(!atomic_compare_exchange_weak(&lock_free_count,&val,val+1));
    }
    pthread_exit(NULL);  
}

int main(void) {

    pthread_t tid[10];
    for(uint16_t i=0; i<5; i++) 
        pthread_create(&tid[i], NULL, adding, NULL);
    for(uint16_t i=5; i<10; i++) 
        pthread_create(&tid[i], NULL, counting, NULL);
    
    for(uint16_t i=0; i<10; i++) 
        pthread_join(tid[i], NULL);

    printf("atomic count = %d\t",a_count);
    printf("non atomic count = %d\n",na_count);
    printf("lock free count = %d\n",lock_free_count);
  
}

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // sleep()
#include <stdlib.h>

void *myturn(void *arg) {
    int i = *(int *)arg;
    int *iptr = (int *)malloc(sizeof(int));
    while (i > 0)
    {
        /* code */
        sleep(1);
        printf("my turn %d\n", i);
        --i;
        (*iptr)++;
    }
    return iptr;
}

void yourturn() {
    int i = 5;
    while (i > 0)
    {
        /* code */
        sleep(2);
        printf("your turn %d\n", i);
        --i;
    }
}

int main(void) {
    int x = 15;
    pthread_t thd ;
    void *rptr ;
    pthread_create(&thd, NULL, myturn, &x);

    yourturn();
    pthread_join(thd, &rptr);
    printf("pthread returns: %d\n", *(int *)rptr);

}

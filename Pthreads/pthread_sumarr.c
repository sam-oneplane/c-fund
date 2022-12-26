#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// consts
#define PTHREAD_SIZE 3
// global vars 
typedef struct Values values;
struct Values {
    int *val_p;
    int offset;
    int arr_size;
};

int vals[] = {36, 5, 43, 4, 21, 16, 7, 9, 13, 17, 8, 18, 28, 1, 11};



void *acc(void *arg) {
    // arg of type values
    int acm = 0;
    int arr_size = (*(values *)arg).arr_size;
    int offset = (*(values *)arg).offset;
    printf("array size:%d  offset:%d\n", arr_size, offset);

    for (int i = offset ; i < arr_size+offset; i++){
        acm += *((*(values *)arg).val_p + i);; 
    }
    printf("acc: %d\n", acm);
    // alloc return value
    int *res = malloc(sizeof(int));
    *res = acm;
    // free allocated parameter : struct values 
    free(arg);
    pthread_exit((void *)res);
}


int main(int argc, char **argv) {

    pthread_t pth[PTHREAD_SIZE];
    int *res;
    int acm = 0;

    // calculate number of threads and input values length 
    const size_t pth_len = sizeof(pth) / sizeof(pth[0]);
    const size_t val_len = sizeof(vals) / sizeof(vals[0]);
    // calculate array per thread length
    int arr_size = (int)(val_len/pth_len); 
    printf("pthreds: %d, values: %d, leap: %d\n",(int)pth_len, (int)val_len, arr_size);
    
    for (size_t i = 0 ; i < pth_len ; i++) {

        // v = { .arr_size = arr_size, .offset = *offset, .val_p = vals } ;
        values *v = malloc(sizeof(values));
        (*v).arr_size = arr_size;
        (*v).offset = (int)i*arr_size;
        (*v).val_p = vals;
        
        if (pthread_create((pth + i), NULL, &acc, v) != 0) {
            perror("Failed to create a thread ");
            return -1;
        }
    }

    for (size_t i = 0 ; i < pth_len ; i++) {
        pthread_join(pth[i], (void **) &res);
        acm += *res ;
        // free result allocation
        free(res);
    }
    printf("array acc : %d\n", acm);

    return 0;
}
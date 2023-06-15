#define __STDC_WANT_LIB_EXT1__ 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>

typedef struct  Vec {
    float a,b ; 
} vec;


vec add_vec(vec v1, vec v2) {
    vec v = {v1.a+v2.a, v1.b+v2.b};
    return v;
}


typedef struct FileContent {
    char *data;
    size_t size;
    int valid;
    
} file_content_t;

file_content_t valid_file_content(const char* path){
    
    FILE *fp = (void *)0;
    file_content_t fc = {.valid = 1};
#if __STDC_VERSION__ == 201112L

// #ifndef __STDC_LIB_EXT1__
// #error "__STDC_LIB_EXT1__not_defined"
// #endif
    fp = fopen(path, "r");
    fc.valid = fp == (void *)0? 1 : 0;
    fseek(fp, 0, SEEK_END);
    fc.size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

#elif __STDC_VERSION__ == 199901L
    fp = fopen(path, "r+");
    if(fp != (void *)0)
        fc.valid = 0;
#endif

    if (fp != (void *)0)
        fclose(fp);
    return fc;    
    
}

int main(void) {
    //1
    vec v1 = {.a= 5.6, .b = 2.2};
    vec v0 = add_vec(v1, (vec){8.6, 9.2});
    printf("add = %f, %f\n", v0.a, v0.b); 
    //2
    file_content_t fc = valid_file_content("modern_c_pthread.c");
    if(fc.valid){
        fprintf(stderr, "error file not found in %s in line %d\n", __FILE__, __LINE__);
    }else {
        printf("file %s is valid with size %d\n", __FILE__, (int)fc.size);
    } 
    return 0;
}



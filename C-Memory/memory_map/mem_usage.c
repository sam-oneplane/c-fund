#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#define MEMALLOC 8192

long get_mem_usage() {
    struct rusage r_usage ;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss; // max resident set size
}

int main() {

    printf("usage: %ld\n", get_mem_usage());
    for (int i=0 ; i < 10; i++) {
        // %ld long decimal
        char *p = malloc(MEMALLOC*sizeof(char));
        memset(p, 1, MEMALLOC);
        printf("usage: %ld\n", get_mem_usage());
    }
}
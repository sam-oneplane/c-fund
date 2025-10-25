#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#define MEMALLOC 1024*10

long get_mem_usage() {
    struct rusage r_usage ;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss; // max resident set size
}

int main() {

    long baseline = get_mem_usage();
    for (int i=0 ; i < 20; i++) {
        // %ld long decimal
        printf("usage: %ld + %ld\n", baseline, get_mem_usage()-baseline);
        char *p = malloc(MEMALLOC);
        memset(p, 1, MEMALLOC);
    }
}
#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef void * (* malloc_func)(size_t);
typedef void (* free_func)(void *);

static malloc_func sysmalloc = NULL;
static free_func sysfree = NULL;
static bool init = false;
static FILE *fp = NULL;
static const char *logfilename = "../files/mem_alloc.log";

void init_check() {
    if(!init) {
        sysmalloc = (malloc_func)dlsym(RTLD_NEXT, "malloc");
        sysfree = (free_func)dlsym(RTLD_NEXT, "free");
        fp = fopen(logfilename, "w");
        init = true;
    }
}

void *malloc(size_t size) {
    init_check();
    void *res = sysmalloc(size);
    fprintf(fp, "M, %lu, %lu\n", (uintptr_t)res, size);
    return res;
}

void free(void *p) {
    init_check();
    fprintf(fp, "F, %lu\n", (uintptr_t) p);
    sysfree(p);
}




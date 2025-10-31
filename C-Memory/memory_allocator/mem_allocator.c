#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h> // dlsym()
#include <stdint.h> // uintptr_t
#include <unistd.h>

#define BUFF_SIZE 128


typedef void * (* malloc_func)(size_t);
typedef void (* free_func)(void *);

static malloc_func sysmalloc = NULL;
static free_func sysfree = NULL;

__attribute__((malloc))
void *malloc(size_t size) {
   
    if (!sysmalloc)
        sysmalloc = (malloc_func)dlsym(RTLD_NEXT, "malloc"); 
    void *res = sysmalloc(size);

    char buf[BUFF_SIZE];
    int len = snprintf(buf, sizeof(buf), "M,%lu,%zu\n", (uintptr_t)res, size);
    if(len>0)
        write(STDERR_FILENO, buf, len);  // Safe: no malloc inside
    
    return res;
}

void free(void *p) {
    if(!sysfree)
        sysfree = (free_func)dlsym(RTLD_NEXT, "free");  

    char buf[BUFF_SIZE];
    int len = snprintf(buf, sizeof(buf), "F,%lu\n", (uintptr_t)p);
    if(len>0)
        write(STDERR_FILENO, buf, len);
    
    sysfree(p);
}


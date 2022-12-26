#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define QUEUE 256 
#define PTHREADS 8
#define TASKS 100

typedef void (*func_ptr)(int, int);

typedef struct Task task_t;
struct Task {
    func_ptr f;
    int x;
    int y;
};




#endif /*__TPOOL_T*/
 
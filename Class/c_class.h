#ifndef __CCLASS_H__
#define __CCLASS_H__

#include <stdlib.h> /* for malloc, free, exit */
#include <stdio.h>  /* perror */

typedef double (*func_ptr)(double);

typedef struct Task task_t;
struct Task {
    func_ptr f;
    int arg;
};

void task_set(task_t *, int, func_ptr);
void task_reset(task_t *);
task_t *task_create(int , func_ptr);
task_t *task_clone(task_t *);
task_t *task_move(task_t *);
void task_free(task_t *);

#endif
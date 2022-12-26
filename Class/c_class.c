#include "c_class.h"


void task_set(task_t *this, int arg, func_ptr f) {
    if (this == NULL) {
        perror("Self task is NULL can't set !\n");
        exit(EXIT_FAILURE);
    }
    this -> arg = arg;
    this -> f = f;
}

void task_reset(task_t *this) {
    if (this == NULL) {
        perror("Self task is NULL can't reset !\n");
        exit(EXIT_FAILURE);
    }
    this -> arg = 0;
    this -> f = NULL;
}


task_t *task_create(int arg, func_ptr f) {

    task_t *task = (task_t *)malloc(sizeof(task_t));
    if (task == NULL) {
        perror("can't alloc task!\n");
        exit(EXIT_FAILURE);
    }
    task_set(task, arg, f);
    return task;
}

void task_free(task_t *this) {
    if (this == NULL) {
        perror("this task is NULL nothing to destroy!\n");
        exit(EXIT_SUCCESS);
    }
    task_reset(this);
    free(this);
}

task_t *task_clone(task_t *this) {

    if (this == NULL) {
        perror("Self task is NULL can't clone\n");
        exit(EXIT_FAILURE);
    }
    task_t *task = (task_t *)malloc(sizeof(task_t));
    if (task == NULL) {
        perror("can't alloc task!\n");
        exit(EXIT_FAILURE);
    }
    task_set(task, this->arg, this->f);
    return task;
}


task_t *task_move(task_t *this) {

    task_t *task = task_clone(this);
    free(this);
    return task;
}


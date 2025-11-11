#include "include/class_rc.h"
#include <stdlib.h>
#include <stdio.h>

struct RcClass {

    void *data;
    MyClassDataDestructor dest;
    size_t rc;
};

RcClass *RcClassNew(void *data, MyClassDataDestructor dest) {

    RcClass *self = malloc(sizeof(RcClass)); 
    if (!self) return NULL;
    self->data = data;
    self->dest = dest;
    self->rc = 1;
    return self;
}

void *RcClassGet(RcClass *self) {

    return self ? self->data : NULL;
}

void RcClassSet(RcClass *self, void *data, MyClassDataDestructor dest) {

    if (!self) return;
    self->data = data;
    self->dest = dest;
}
// this is like copy assignment operator
RcClass *RcClassRef(RcClass *self) {
    if (self) self->rc++ ;
    printf("rc = %ld\n", self->rc);
    return self;
}

void RcClassUnRef(RcClass *self) {

    if (!self) return;
    --(self->rc);
    printf("rc =  %ld\n", self->rc);
    if (self->rc == 0) {
        
        free(self);
    }
}
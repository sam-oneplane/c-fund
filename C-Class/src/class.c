#include "include/class.h"
#include <stdlib.h>

struct MyClass {

    void *data;
    MyClassDataDestructor dest;
};

MyClass *MyClassNew(void *data, MyClassDataDestructor dest) {

    MyClass *self = malloc(sizeof(MyClass)); 
    if (!self)return NULL;
    self->data = data;
    self->dest = dest;
    return self;
}

void *MyClassGet(MyClass *self) {

    return self ? self->data : NULL;
}

void MyClassSet(MyClass *self, void *data, MyClassDataDestructor dest) {

    if (!self) return;
    self->data = data;
    self->dest = dest;
}

void MyClassDest(MyClass *self) {
    if (!self) return;
    printf("free self at %p\n", self);
    free(self);
}


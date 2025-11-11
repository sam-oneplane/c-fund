#ifndef CLASS_H
#define CLASS_H

#include <stddef.h>
#include <stdlib.h>

# ifdef __cplusplus
extern "C" {
# endif

typedef struct MyClass MyClass;
typedef void (*MyClassDataDestructor)(void *);

MyClass *MyClassNew(void *data, MyClassDataDestructor dest) ;
void *MyClassGet(MyClass *self);
void MyClassSet(MyClass *self, void *data, MyClassDataDestructor dest);
void MyClassDest(MyClass *self);

static void MyClassAutoClean(MyClass **obj) {
    MyClassDest(*obj);
    *obj = NULL;
}

#ifdef __GNUC__
#define MYCLASS_AUTOCLEAN __attribute__((cleanup(MyClassAutoClean)))
#else
#define MYCLASS_AUTOCLEAN
#endif


# ifdef __cplusplus
}
# endif

#endif




#ifndef CLASS_RC_H
#define CLASS_RC_H

#include <stddef.h>
#include <stdlib.h>

# ifdef __cplusplus
extern "C" {
# endif

typedef struct RcClass RcClass;
typedef void (*MyClassDataDestructor)(void *);

RcClass *RcClassNew(void *data, MyClassDataDestructor dest) ;

void *RcClassGet(RcClass *self);
void RcClassSet(RcClass *self, void *data, MyClassDataDestructor dest);

RcClass *RcClassRef(RcClass *self);
void RcClassUnRef(RcClass *self);


# ifdef __cplusplus
}
# endif

#endif
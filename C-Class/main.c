#define _GNU_SOURCE

#include "include/class.h"
#include "include/class_rc.h"
#include <string.h>
#include <stdio.h>


/*
1. mkdir build
2. cd build
3. cmake ..
4. cmake --build .
5. run executable inside build/bin 
*/


void str_free(void *data) {
    free(data);
}

void class_creator() {
    char *txt = strdup((char *)"hello world!");
    MYCLASS_AUTOCLEAN MyClass *obj = MyClassNew(txt, str_free);
    char *ret = MyClassGet(obj);
    printf("my class say: %s\n", ret);
    free(txt);

    char *txt2 = strdup("good night!");
    MyClassSet(obj, txt2, str_free);    
    ret = MyClassGet(obj);
    printf("my class say: %s\n", ret);
    free(txt2);
}

void rc_class_creator() {

    char *txt = strdup((char *)"holla amigos!");
    RcClass *obj = RcClassNew(txt, str_free);
    char *ret = (char *)RcClassGet(obj);
    printf("rc class say: %s\n", ret);
    RcClass *obj2 = RcClassRef(obj);
    
    ret = RcClassGet(obj2);
    printf("rc class say: %s\n", ret);
    
    free(txt);
    RcClassUnRef(obj2);
    RcClassUnRef(obj);
}

int main() {

    class_creator();
    rc_class_creator();
    return 0;
}

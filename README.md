# C compiler

## storage-class specifiers:

    auto (default)
    extern
    static
    thread_local (macro _Thread_local)
    typedef (sentactic convenience)
    register


    extern int n    // non definitive decliration (n defined someware else)

# storage duration

    static      - allocated in memory when programs starts ans stays there until its ending (init to 0)
    thread      - allocated when thread is starting and end when the thread dies
    automatic   - allocated with a block (function for example)
    dynamic     - allocated in run time by malloc to the heap freed by free(ptr)


# linkage

    internal
    external
    none

## external linkage

    file1.c

    extern int x = 0 ;  // defenition
    int const y = 42;

    file2.c 

    extern int x        // declaration non defined
    int const y

    int f(int) // defenition are external by default



# c99 & c11-c18 new fatures

## <stdio.h>  


    EOF: macro
    FILE: type 
    printf(): function
    stdout:   object
    

    typedef struct _iobuf FILE

## definision of bool <stdbool.h>

    dypedef enum {true, false} _Bool; // keyword

##  macro for standart C complier
    __STDC__ 
    __STDC_VERSION__

    exp:    #if __STDC_VERSION__ == 201710L (c18)


## c examples :
    <stdlib.h>
    long int atol(char const *ptr) ;
    long int labs(long int num) ;

    typedef char sint8;
    typedef unsigned long uint32


## integer types <stdint.h>

    int8_t 
    uint32_t
    int_least8_t // samllest type that can hold 8bit signed number
    int_fast8_t  // fasted type that can hold 8bit signed number in terms of performence
    intmax_t
    uintmax_t
    intptr_t    // signed int that can hold a value of a pionter
                // if sizeof(void *) > sizeof(intmax_t) this value does not exists


## compile time info 

    __func__    // what id the function name currently compiling (for error msg)

    defenition :  static chat const __func__[] = "function name";

    code example :

    #define enter() printf("enter:%s\n", __func__)
    #define leave() printf("leave:%s\n", __func__)

    void foo(...) {
        enter();        // enter foo()
        ...

        leave();        // leave foo()
    }


## inline - best in file.h
    

    inline int max_int(int x, int y) {
        return x > y ? x : y;
    }


    mv = max_int(*p++, *q++) ;

    int (*p)(int, int) = &max_val  //addr of a function is legal
    // create a non inline copy of inline func

    // decleration  is legal
    extern inline int max_int(int x, int y) 


## <complex.h>  x+ yi where i^2 = -1

    _Complex & _Imaginary comes in :

    float | double | long double  _Complex type
    float | double | long double  _Imaginary type


    example :
    _Complex double z;

## literals 

    rational numbers: 

    rational conat one_half = {1,2}  
    same as :
    typedef struct rational rational
    staruct rational {
        int x,y;
    };

## copmuned literals 

## 1.
    bool ret_eq(rational lo, rational ro) {
        return (lo.num == ro.num) && (lo.num == lo.den);
    }

    rational r;
    if (ret_eq(r, (rational){1,2} ) ) {
        ... 
    }
    // (rational){1,2}  casting 


## 2.
    enum {m = 7};
    enum {n = m * sizeof(int)};

    int d[m];
    if ( memcmp(d, (int[m]){1,2,3,4,5,6,8}), n == 0) {
        ...
    }

## desigmated initializers 

    typdef union glop glop ;
    union glop {
        int i;
        float f;
    }

    glop g1 = {.i = 10};
    glop g2 =  {.f = 12.4};

## same with structs 

    typdef struct glop glop ;
    struct glop {
        int i;
        float f;
    }

    struct s1  = {.i = 10, .f = 13.7};


## arrays : 

    a[10] = {0,0,9,7,0};
    a[10] = {[2]=9 , [3]=7};


## malloc array size in run time 

    void foo(size_t n) {
        int *x = malloc(n * sizeof(int));
        for (size_t i = 0 ; i < n ; i++) {
            // x[i] manipulation ...

        }
        free(x);
    }

    or you can do :

    void foo(size_t n) {

        int x[n] ; //rem :  dont need to alloc anf free 

        for (size_t i = 0 ; i < n ; i++) {
            // x[i] manipulation ...

        }

    }

    sizeof() is a runtime compiled for var length array


## flexible array member : 

    typdef struct glop glop ;
    struct glop {
        header h;
        data d[];   // flexible by size
    }


## const, volatile, restrict : as type qualifier



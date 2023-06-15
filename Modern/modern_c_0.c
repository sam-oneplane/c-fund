#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <complex.h>
#include <stdlib.h> //strcpy
#include <string.h> //memcmp
#include <uchar.h>
#include <errno.h>
/*
EOF (macro)
FILE (type)
printf (function)
stdout (object)
*/

// 1. 
/*  typedef struct _iobuf FILE; // FILE type def
    typedef enum {false, true} bool;
*/

// 2.
int _reserved;  // reserved for global scope ; dont use _name 
int __reserved; // reserved for all uses  

// 3. std C18/C11/C99/STDC
#if __STDC_VERSION__ == 201710L

#elif __STDC_VERSION__ == 201112L

#elif __STDC_VERSION__ == 199901L

#elif __STDC__ == 1

#else
#endif


// 4. exact width int types
typedef char sint8;  // optional , depend on arcitucture
typedef unsigned long uint32;
uint32_t i32bit;
uint_least16_t ul16bit; // smallest type for uint16 bits
uint_fast16_t uf16bit;  // fastest type that can represent uint16 bits
intmax_t imax;
intptr_t iptr ; // signed int that can hold a value of a ptr

bool check_size(void) {
    // if true no intptr_t is avalible
    return (sizeof(void *) > sizeof(intmax_t)) ;
}


// 5.
void error_info(void) {
    fprintf(stderr, "error in %s at line %d at func %s", __FILE__, __LINE__, __func__);
}



typedef int (*func_p)(int*, int*);
// 6 inline defenition & decleration in header file
inline int max_val(int* x, int* y) {
    return (*x) > (*y)? (*x) : (*y);
} 



// 7. complex numbers

float _Complex c = _Complex_I;
//_Imaginary float  ;
complex double c1 = 8 + 5*I;
//double imaginary; 


// 8. Compound Literals
typedef struct rational rational;
struct rational
{
    long num,den;
};

const rational one_half = {1,2};


enum {m=7};
int arr[m];

bool comp_arr(const int size) {
    if (memcmp(arr, (int []){2,3,4,8,9,1,0}, m*sizeof(int)) == 0) {
        printf("equal\n");
    }
}

// 9. Designated initializers
typedef union  glop glop;
union  glop
{
    int i;
    double d;
};



int a[10] = {[3] = 8, [6] = 2}; // [0,0,0,8,0,0,2,0,0,0]


// 10. var length arrays replace malloc() 
void foo(int x, int y) {
    int a[x][y]; // can't be static or extern
    for (size_t i=0; i<x; i++) {
        a[i][y] = -1;
    }
}

typedef struct packet {
    char* header;
    int data[]; // flexible array member
}packets;


// 11. restrict : type qualifier avoid overlapping of pointers
char *strcpy(char *restrict s1, const char* restrict s2);


// 12. _Generic assertion
float minf(float x, float y);
int mini(int x, int y);

#define min(x,y) _Generic((x), float: minf(x,y), int: mini(x,y));  

//C11 only
#define cbrt(X) _Generic((X), long double: cbrtl, default: cbrt, float: cbrtf)(X)

/*
_Static_assert
_Atomic
_Thread_local
_Noreturn
_Generic
_Alignas // memory
restrict // pointers access
*/

// 12. anonymous struct/union
typedef struct T T;
struct T {
    uint16_t x;
    union // anonymous 
    {
        char *index;
        uint16_t y;
    };
};

//  13. _Aligned memory for obj
// ** The _Alignas specifier can only be used when declaring objects that are not bit-fields, 
//  and don't have the register storage class.
//  It cannot be used in function parameter declarations, and cannot be used in a typedef.
// ** every object of type struct sse_t will be aligned to 16-byte boundary
// (note: needs support for DR 444)
struct sse_t
{
  _Alignas(16) float sse_data[4];
};
// allocates size bytes of memory with alignment algn and returns a pointer to the allocated memory.
void *aligned_alloc(size_t algn, size_t size); // <stdalign.h>

// 14.
//_Noreturn declares a function that does not return. 
// This new functions specifier has two purposes: 
//      suppressing compiler warnings on a function that doesn't return, 
//      enabling certain optimizations that are allowed only on functions that don't return.

_Noreturn void func (); //C11, func never returns

// 15. Unicode
char32_t *c32 ;  // UTF-16 
char16_t *c16 ;  // UTF-8


// 16. bound cheacking functions
//C11, safe version of strcat for microsoft visual-c
int strcat_s(char * restrict s1, 
            size_t s1max, 
            const char * restrict s2);


char *gets_s(char * restrict buffer, size_t nch); // getc() deprecated since C99



int main(void) {
    creal(c);
    cimag(c1);    
    one_half.den;
    glop g1 = {.i = 7};
    glop g2 = {.d = 2.4};

    size_t n = 10 ;
    packets *p = malloc(sizeof(packets)+ n*sizeof(int)) ; // packets + array alloc

    T t;
    t.y=16; // set union uint value

    return 0;
}
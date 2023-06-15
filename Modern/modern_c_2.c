#include <stdio.h>


// modern C dynamic array (std::vector<T> vec;)
#define dynarray(T) T*

typedef struct dynarray_info {
    size_t size;
    size_t capacity;
    size_t element_size;
} dynarray_info;

#define dynarray_add(arr, ...) dynarray_ensure_capacity(arr); (*arr)[dynarray_size(*arr)] = __VA_ARGS__
#define dynarray_init(T, size) (T *)malloc(size* sizeof(T)+ sizeof(dynarray_info))

int main(void) {

    dynarray(int) arr = dynarray_init(int, 10);
    dynarray_add(&arr, 90);

    return 0;
}

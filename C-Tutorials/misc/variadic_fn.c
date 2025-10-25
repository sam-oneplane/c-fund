#include <stdarg.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint16_t x,y;
} Numbers;

Numbers add_nums(Numbers n1, Numbers n2) {
    Numbers z = {n1.x + n2.x, n1.y + n2.y} ;
    return z;
}

// count defines the number of parameters (...) into sum func using lib <stdarg.h> 
float sum_n(int count, ...) {

    printf("num of params : %d\n", count);
    va_list args;
    va_start(args, count);
    float total = 0 ;
    for(int i = 0 ; i < count; i++) {
        // define args as float
        total += va_arg(args, float);
    }
    va_end(args);
    return total;
}

int main(void) {
    // undefind number of varibles using lib <stdarg.h> 
    printf("sum : %.3f\n", sum_n(4, 2.4, 1.1, 5.6, 6.0));

    Numbers n1 = {3,4};
    Numbers n = add_nums(n1, (Numbers){1,9});
    return (n.x + n.y);
}
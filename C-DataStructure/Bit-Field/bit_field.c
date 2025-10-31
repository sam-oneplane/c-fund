#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct counters{
    uint16_t first: 4;
    uint16_t second: 4;
    uint16_t third: 8; 
} __attribute__((packed));

#define SET_BIT(BF, N) BF |= ((uint64_t)0x0000000000000001 << N)
#define CLR_BIT(BF, N) BF &= ~((uint64_t)0x0000000000000001 << N)
#define IS_BIT_SET(BF, N) ((BF >> N) & 0x1)

#define LOOPS 50

void set_counts() {
    struct counters *counts = malloc(sizeof(struct counters));
    counts->first=0;
    counts->second=0;
    counts->third=0;

    printf("sizeof counts: %ld\n", sizeof(*counts));
    for(uint16_t i = 0; i < LOOPS; i++ ) {
        printf("%d, %d, %d\n", counts->first++, counts->second++, counts->third++);
    }

    free(counts);
}

void set_macros() {
    uint64_t array_of_bits = 0 ;
    SET_BIT(array_of_bits, 1);
    SET_BIT(array_of_bits, 16);
    SET_BIT(array_of_bits, 4);
    SET_BIT(array_of_bits, 8);
    SET_BIT(array_of_bits, 11);
    SET_BIT(array_of_bits, 27);
    SET_BIT(array_of_bits, 39);

    CLR_BIT(array_of_bits, 11);
    
    for (int i = 0 ; i < 64; i++ ) {
        if(IS_BIT_SET(array_of_bits, i))
            printf("+");
        else
            printf(".");
    }
    printf("\n");
}

int main() {
    
    set_counts();
    set_macros();
 
    return 0;
}
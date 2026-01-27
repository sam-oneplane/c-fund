#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 6

bool remove_element(int *arr, int len, int indx) {

    if (indx < 0 || indx >= len) {
        return false;
    }
    /* used in overlap memory blocks */
    memmove(arr+1, arr, sizeof(int)*indx);
    arr[0] = 0;

    return true;
}


int main(void) {
    int vals[SIZE] = {1,3,5,7,9, 11};
    remove_element(vals, SIZE, 2);
    remove_element(vals, SIZE, 4);
    remove_element(vals, SIZE, 3);

    for (int i=0; i < SIZE; i++)
        printf("%d\t", vals[i]);
    printf("\n");
}
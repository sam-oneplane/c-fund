#include <stdio.h>
#include <stdint.h> // uint32_t
#include <stdlib.h> // malloc , free
#include <string.h> // memcpy , memset, memcmp

#define BUFF_SIZE 4096
#define OFFSET 100

typedef struct node {
    uint32_t is_valid : 1;
    uint32_t size : 15;
    struct node *next;
} node_t;


void mem_cpy_to_stack_and_heap() {

    node_t node0 = {.is_valid = 1 , .size = 20, .next = NULL};
    

    /* Copy to stack*/
    node_t node1;
    memcpy(&node1, &node0, sizeof(node_t));
    printf("node1 info: (is_valid: %d, size: %d, next_ptr %p)\n", node1.is_valid, node1.size, node1.next);

    node_t *node_h ; 
    if ((node_h = malloc(sizeof(node_t))) != NULL ){
        /*Copy to heap*/
        memcpy(node_h, &node0, sizeof(node_t));
        printf("node on heap info: (is_valid: %d, size: %d, next_ptr %p)\n", node_h->is_valid, node_h->size, node_h->next);
        free(node_h);
    } 

}

void mem_cpy_to_buffer() {

    node_t node = {.is_valid = 1 , .size = 20, .next = NULL};

    char *buff;
    if((buff = malloc(BUFF_SIZE*sizeof(char))) == NULL) {
        fprintf(stderr, "malloc has failed! %p\n", buff);
    }

    memset(buff, 0xCC, BUFF_SIZE);
    memcpy(buff+OFFSET, &node, sizeof(node_t));
    // read buff + OFFSET location and cast into info_t 
    node_t *node_ptr = (node_t *)(buff+OFFSET);
    printf("node pointer info: (is_valid: %d, size: %d, next_ptr %p)\n", 
        node_ptr->is_valid, node_ptr->size, node_ptr->next);

    printf("buffer at location 0 is : %02x\n",buff[0]);
    free(buff);
}

int main() {
    mem_cpy_to_stack_and_heap();
    mem_cpy_to_buffer();
}


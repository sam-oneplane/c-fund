#include<stdio.h>
#include<stdatomic.h>
#include<stdlib.h>
#include<stdint.h>

//the node type in the stack
typedef struct _Node {
    __uint128_t data;
    struct _Node* next;
} Node;

//the stack
typedef struct _lfstack_t {
    __uint128_t tag;
    Node *head;
} lfstack_t;
 
//the push function
void lfstack_push(_Atomic lfstack_t *lfstack, __uint128_t value) {
    lfstack_t next;
    lfstack_t orig = atomic_load(lfstack);  
    /*here we need a local copy of lfstack, however, lfstack is a pointer
    we could not get the content from a struct pointer atomically by assignmen
    C11 provides us a function to atomically get the content from the location that 
    A atomic type pointer points to. */ 

    // Step 1 : create new node and set value
    Node *node = malloc(sizeof(Node));
    node->data = value;
    do{
        // Step.2 set node to be the 1st node, and set local.head node = new node  
        node->next = orig.head; 
        next.head = node; 
        next.tag = orig.tag + 1;
    }while(!atomic_compare_exchange_weak(lfstack, &orig, next)); 
    // if the lfstack is not changed by others, apply the local change of head to it
    // else  orig = atomic_load(lfstack);
}

 //pop function
int lfstack_pop(_Atomic lfstack_t *lfstack) {

    lfstack_t next;
    lfstack_t orig = atomic_load(lfstack);
    do{
        if(orig.head == NULL) { //return when the stack is empty 
            return -1;
        }
        next.head = orig.head->next; //set the head to the next node
        next.tag = orig.tag + 1;
    } while(!atomic_compare_exchange_weak(lfstack, &orig, next)); 
    //if the head of stack is not changed, update the stack

    printf("poping value %llx\n",(unsigned long long)orig.head->data); //just want to see the poping value.
    free(orig.head); // free the poping node

    return 0;
}
#include<stdio.h>
#include<stdatomic.h>
#include<stdlib.h>
#include<stdint.h>


//queue of data elements in the node 
typedef struct _Node {
    __uint128_t data;
    struct _Node* next;
} Node;

//the stack queue of nodes 
typedef struct _lfstack_t {
    __uint128_t tag; // define the depth of the Nodes in lfstack
    Node *head;
} lfstack_t;
 
//the push function
void lfstack_push(_Atomic lfstack_t *lfstack, _Atomic __uint128_t *dat) {
    lfstack_t sttmp;
    lfstack_t storig = atomic_load(lfstack);  
    /*here we need a local copy of lfstack, however, lfstack is a pointer
    we could not get the content from a struct pointer atomically by assignmen
    C11 provides us atomic_load to atomically get the content from the location that 
    A atomic type pointer points to. */ 

    // Step 1 : create new node and set value
    Node *node = malloc(sizeof(Node));
    node->data = atomic_fetch_add(dat, 1);
    do{
        // Step.2 set node to be the 1st node, and set local.head node = new node  
        node->next = storig.head; 
        sttmp.head = node; 
        sttmp.tag = storig.tag + 1;
    }while(!atomic_compare_exchange_weak(lfstack, &storig, sttmp));
    printf("pushing to tag %lld, value %llx\n",(unsigned long long)sttmp.tag , (unsigned long long)sttmp.head->data);
    // if the lfstack is not changed by others, apply the local change of head to it
    // else  storig = atomic_load(lfstack);
}

 //pop function
int lfstack_pop(_Atomic lfstack_t *lfstack) {

    lfstack_t sttmp;
    lfstack_t storig = atomic_load(lfstack);
    do{
        if(storig.head == NULL) { //return when the stack is empty 
            return -1;
        }
        sttmp.head = storig.head->next; //set the head to the next node
        sttmp.tag = storig.tag + 1;
    } while(!atomic_compare_exchange_weak(lfstack, &storig, sttmp)); 
    //if the head of stack is not changed, update the stack

    printf("poping {tag,value}, %lld, %llx\n",(unsigned long long)sttmp.tag, (unsigned long long)storig.head->data); //just want to see the poping value.
    storig.head = NULL; 

    return 0;
}
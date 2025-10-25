#include <stdlib.h>
#include "queue_t.h"

node_t *head = NULL;
node_t *tail = NULL;

void enqueue(int *client_socket) {
    node_t *node = malloc(sizeof(node_t));
    node->client_socket = client_socket;
    node->next = NULL;

    if (tail == NULL) // first node
        head = node;
    else
        tail->next = node; // add node to queue
    tail = node;    
}

int *dequque() {
    if (head == NULL)
        return NULL;
    node_t *tmp = head;
    head = head->next;
    if(head == NULL) tail = NULL; // empty queue
    int *res = tmp->client_socket;
    free(tmp);
    return res;
}
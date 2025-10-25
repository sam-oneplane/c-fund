#ifndef QUEUE_T_H
#define QUEUE_T_H

struct node {
    struct node *next;
    int *client_socket;
};
typedef struct node node_t;

void enqueue(int *client_socket);
int *dequque();

#endif
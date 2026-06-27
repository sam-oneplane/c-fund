// clang tcpserver.c common.c queue_t.c -o tcps -lpthread -I. -Wall -std=c11
#define _GNU_SOURCE
#include "common.h"
#include "queue_t.h"
#include <stdio.h>

#ifndef __STDC_NO_THREADS__
   
#include <threads.h>


void *handle_conn(void *p_client_socket);
int thread_func(void *arg);

thrd_t thread_pool[THREAD_POOL_SIZE];
mtx_t mutex;
cnd_t cond_var;

int main(int argc, char **argv) {
    mtx_init(&mutex, mtx_plain);
    cnd_init(&cond_var);
    int server_socket, client_socket, addr_size;
    struct sockaddr_in servaddr, clientaddr;
    
    // create thread pool
    for(int i=0; i<THREAD_POOL_SIZE; i++) {
        thrd_create(&thread_pool[i], thread_func, NULL);
    }

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "socket error");
    
    // set server addr obj 
    memset(&servaddr, 0 , sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // htonl htons proper data tranmision over the http network
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);
    // bind server addr to socket
    check((bind(server_socket, (struct sockaddr *) &servaddr, sizeof(servaddr))), "bind error");

    check((listen(server_socket, SERVER_BACKLOG) ), "listen error");

    // Start enqueue client requests
    for( ; ; ) {
        
        printf("wating dor connection in port %d\n", SERVER_PORT);
        fflush(stdout);

        addr_size = sizeof(struct sockaddr_in);
        // except new connection
        check(client_socket = 
            accept(server_socket, 
            (struct sockaddr *) &clientaddr,
            (socklen_t *)&addr_size), "accept falied");

        
        int *pclient = malloc(sizeof(int));
        *pclient = client_socket;
        mtx_lock(&mutex);
        enqueue(pclient);
        cnd_signal(&cond_var);
        mtx_unlock(&mutex);
    } // for loop
}

int thread_func(void *arg) {

    for( ; ; )  {
        int *pclient;
        mtx_lock(&mutex); 
        if((pclient = dequque()) == NULL) {
            /* when the thread is waiting for the condition variable signal 
            it is realising the mutex lock so other threads can access the queue 
            and lock it themselves */
            cnd_wait(&cond_var, &mutex);
            pclient = dequque();
        }
        mtx_unlock(&mutex);
        handle_conn(pclient);
    }
    return 0;
}

void *handle_conn(void *p_client_socket) {

    /*
        1. get client file path (actualpath)
        2. read the file if exists 
        3. count nuber of lines and print to stdout
    */

    char buffer[MAX_LINE];
    size_t bytesrd;
    int msgsize = 0;
    char actualpath[PATH_MAX+1];

    // copy and free parameter
    int client_socket = *(int *)p_client_socket;
    free(p_client_socket);

    // read client's massage using client socket file descriptor
    while((bytesrd = read(client_socket, buffer+msgsize, sizeof(buffer)-msgsize-1)) > 0) {
        msgsize += bytesrd;
        if(msgsize > MAX_LINE-1 || buffer[msgsize-1] == '\n') break; // ens of msg
    }
    check(bytesrd, "recieve error");
    buffer[msgsize-1] = 0; // null terminate the buffer using '0'

    printf("request: %s\n", buffer);
    fflush(stdout);
    // check for client file path content request
    if(realpath(buffer, actualpath) == NULL) {
        printf("error: bad path: %s\n", buffer);
        close(client_socket); // client_socket is a fd
        return NULL;
    }

    // read file and snd contant to client
    FILE *fp = fopen(actualpath, "r");
    if (fp == NULL) {
        printf("error: open path: %s\n", buffer);
        close(client_socket); // client_socket is a fd
    }

    // else read buffer
    while((bytesrd = fread(buffer, 1, MAX_LINE, fp)) > 0) {
        printf("sending %zu bytes from thread %p\n", bytesrd, (void *)thrd_current());
        write(client_socket, buffer, bytesrd); // write buffer to client_socket fd
    }

    close(client_socket);
    fclose(fp);
    printf("closing server connection\n");
    return NULL;
}
#endif
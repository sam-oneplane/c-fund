// clang selectserver.c common.c  -o selectserv -I. -Wall -std=c11
#define _GNU_SOURCE
#include "common.h"

int accept_new_conn(int server_socket, struct sockaddr_in *clientaddr);
void *handle_conn(int client_socket);

int main(int argc, char **argv) {

    int server_socket, client_socket;
    struct sockaddr_in servaddr, clientaddr;

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "socket error");
    
    // set server addr obj 
    memset(&servaddr, 0 , sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // htonl htons proper data tranmision over the http network
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    check((bind(server_socket, (struct sockaddr *) &servaddr, sizeof(servaddr))), "bind error");
    check((listen(server_socket, SERVER_BACKLOG) ), "listen error");

    fd_set current_sockets, ready_sockets;
    // INIT CURRENT SET
    FD_ZERO(&current_sockets);
    FD_SET(server_socket, &current_sockets);
    int addtive_max_socktets = server_socket;
    printf("addtive_max_socktets: %d\n", addtive_max_socktets);

    while (true) {
        /* select is destructive so.. */
        ready_sockets = current_sockets;
        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0 ) {
            err_n_die("select error");
            exit(EXIT_FAILURE);
        }

        for (int i=0; i <= addtive_max_socktets; i++) {
            if(FD_ISSET(i, &current_sockets)) {
                if(i == server_socket) {
                    // this is a new connection
                    client_socket = accept_new_conn(server_socket, &clientaddr);
                    FD_SET(client_socket, &current_sockets);
                    if (client_socket > addtive_max_socktets) {
                        addtive_max_socktets = client_socket;
                        printf("addtive_max_socktets: %d\n", addtive_max_socktets);
                    }
                }else {
                    // handle and clear connection
                    handle_conn(i);
                    FD_CLR(i, &current_sockets);
                }

            }
        }

        // printf("wating dor connection in port %d\n", SERVER_PORT);

    }
    
    return EXIT_SUCCESS;
}

void *handle_conn(int client_socket) {

    char buffer[MAX_LINE];
    size_t bytesrd;
    int msgsize = 0;
    char actualpath[PATH_MAX+1];

    // copy and free parameter
    // int client_socket = *(int *)p_client_socket;
    // free(p_client_socket);

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
        printf("sending %zu bytes\n", bytesrd);
        write(client_socket, buffer, bytesrd); // write buffer to client_socket fd
    }

    close(client_socket);
    fclose(fp);
    printf("closing server connection");
    return NULL;
}

int accept_new_conn(int server_socket, struct sockaddr_in *clientaddr) {

    int client_socket;
    int addr_size = sizeof(struct sockaddr_in);
    // except new connection and create client socket
    check(client_socket = 
        accept(server_socket, 
        (struct sockaddr *) &clientaddr,
        (socklen_t *)&addr_size), "accept falied");

    return client_socket;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFSIZE 4096
#define SOCKETERROR (-1)

int check(int exp, const char *msg) ;

int main(int argc, char**argv) {

    if(argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    int udp_socket ; // = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in peer_addr; /*recived addr*/
    struct sockaddr_in my_addr = {.sin_family = AF_INET,
                                .sin_addr.s_addr = INADDR_ANY,
                                .sin_port = htons(port)};
    char buffer[BUFFSIZE];

    if((udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) <= 0){
        perror("problem with udp socket creation");
        return EXIT_FAILURE;
    }

    /* bind socket to addr and port*/
    int res = bind(udp_socket, (struct sockaddr *)&my_addr, sizeof(my_addr));
    check(res, "could not bind socket");
    /* recvfrom udp_socket fd */
    socklen_t addr_len  = sizeof(peer_addr);

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    
    check(setsockopt(udp_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)), 
           "setting timeout failed!");

    int byte_recieved = recvfrom(udp_socket,
                                buffer,
                                BUFFSIZE, 
                                0, 
                                (struct sockaddr *)&peer_addr, 
                                &addr_len);

    if ((byte_recieved == SOCKETERROR) && (errno == EWOULDBLOCK)) {
        printf("socket timed out\n");
        return EXIT_FAILURE;
    }
    else
        check(byte_recieved, "didn't get data");

    printf("package recivied from %s:%d with massage %s\n",
         inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port), buffer);

    close(udp_socket);
    return EXIT_SUCCESS;

}

int check(int exp, const char *msg) {
    if (exp == SOCKETERROR) {
        perror(msg);
        exit(1);
    }
   return exp;
}

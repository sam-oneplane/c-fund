#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char**argv) {

    if(argc != 4) {
        printf("usage: %s <peer-ip> <peer-port> <massage>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *peer_ip = argv[1];
    int peer_port = atoi(argv[2]);
    const char *massage = argv[3];

    struct sockaddr_in peer_addr = {.sin_family = AF_INET, .sin_port = htons(peer_port)};

    /* conver to binary version for socket */
    if(inet_pton(AF_INET, peer_ip, &(peer_addr.sin_addr)) <= 0) {
        perror("problematic ip address\n");
        return EXIT_FAILURE;
    }

    /* create a socket as a file descriptor */
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket <= 0) {
        perror("problem with udp socket creation");
        return EXIT_FAILURE;
    }

    if (sendto(udp_socket, 
               massage, 
               strlen(massage)+ 1, 
               0, 
               (struct sockaddr *)&peer_addr,
               sizeof(peer_addr)) < 0 )
    {
        perror("failed to send massage\n");
        return EXIT_FAILURE;
    }

    printf("massgae %s to %s:%d\n", massage, peer_ip, peer_port);
    close(udp_socket); /* like fd open and close */ 

    return EXIT_SUCCESS;
}
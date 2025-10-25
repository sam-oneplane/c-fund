#define _GNU_SOURCE
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("usage: %s <hostname>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *hostname = argv[1];

    struct addrinfo hint;
    struct addrinfo *result;

    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC; //ipv4 addr family un specified
    /* hint.ai_socktype = SOCK_STREAM | SOCK_DGRAM */

    int status = getaddrinfo(hostname, NULL, &hint, &result);
    if (status) {
        printf("getaddrinfo() error\n");
        return EXIT_FAILURE;
    }

    struct addrinfo *tmp = result;
    while(tmp != NULL) {

        char addr_str[INET6_ADDRSTRLEN];
        void *addr;
        if (tmp->ai_family == AF_INET)
            addr = &((struct sockaddr_in *)tmp->ai_addr)->sin_addr; // v4
        else
            addr = &((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr; // v6

        
        inet_ntop(tmp->ai_family, addr, addr_str, sizeof(addr_str));
        printf("Entry\n");
        printf("\tType: %d\n",tmp->ai_socktype);
        printf("\tFamily: %d\n",tmp->ai_family);
        printf("\tIP Addr: %s\n",addr_str);

        tmp = tmp->ai_next;
    }

    freeaddrinfo(result);

    return EXIT_SUCCESS;
}
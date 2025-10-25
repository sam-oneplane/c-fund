// clang tcpclient.c common.c -o client -I. -Wall -std=c11
#define _GNU_SOURCE
#include "common.h"


int http_get(char *addr, short port) {

    int sockfd;
    int sendbytes;
    struct sockaddr_in servaddr;
    char sendline[MAX_LINE];

    
    // create socket: file like end point
    // AF_INET : internet socket
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0)
        err_n_die("Error while creating the socket");
    
    memset(&servaddr, 0 , sizeof(servaddr)); /**/
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port); /*host to network short*/

    /* convert ip address from text to binary*/
    if(inet_pton(AF_INET, addr, &servaddr.sin_addr) <= 0)
        err_n_die("usage %s <server addr>", addr);

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))
        err_n_die("connect failed");
    
    /* prepare a line when connect */
    sprintf(sendline, "GET / HTTP/1.1\r\nConnection: close\r\n\r\n");
    sendbytes = strlen(sendline);

    /* send http request */
    if (write(sockfd, sendline, sendbytes) != sendbytes)
        err_n_die("write error");
    /*
    memset(recvline, 0 , MAX_LINE);
    while ( (n = read(sockfd, recvline, MAX_LINE-1) ) > 0 )
        printf("%s", recvline);
    */
    return sockfd;
}

void print_usage(char *progname) {
    printf("usage:\n");
    printf("\t%s http <server ip addr>\n", progname);
    printf("\t%s file <file name>\n", progname);
    printf("\t%s stdin\n", progname);
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    char *src = argv[1];
    FILE *input_src = NULL;
    int num_lines = 0;

    char buffer[MAX_LINE];

    /* handle source */
    if (strcmp(src, "stdin") == 0) {
        input_src = stdin; // stdin is a pipe to a file pointer
    } else if (strcmp(src, "file") == 0) {
        input_src = fopen(argv[2], "r");
    } else if (strcmp(src, "http") == 0) {
        int socket = http_get(argv[2], HTTP_SERVER_PORT);
        /* socket is a file descriptor so we can use fdopen() */
        input_src = fdopen(socket, "r");
    } else {
        printf("wrong input parsing\n");
        return EXIT_FAILURE;
    }

    if (input_src == NULL) {
        printf("can't open source\n");
        return EXIT_FAILURE;
    }

    while (!feof(input_src)) {
        if (fgets(buffer, MAX_LINE, input_src)) num_lines++;
    }

    fclose(input_src);
    printf("we read %d lines\n", num_lines);

    return EXIT_SUCCESS;
}
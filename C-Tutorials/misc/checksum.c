#define _GNU_SOURCE
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char checksum_add;
    unsigned char checksum_xor;
}CheckSum ; 


char *currapt_msg(const char *msg, int num_bits) {
    char *res = strdup(msg); // duplicate a string using malloc 

    for (int i = 0 ; i < num_bits; i++) {
        int byteidx = rand() % strlen(msg);
        int bitidx = rand() % 8;

        res[byteidx] ^= 1 << bitidx;
    }
    return res;
}

CheckSum *checksum(const char *msg, int length) {
    CheckSum *res = malloc(sizeof(CheckSum));
    res->checksum_add = 0;
    res->checksum_xor = 0;
    for (int i=0 ;i < length; i++) {
        res->checksum_add += msg[i];
        res->checksum_xor ^= msg[i];
    }
    return res;
} 

int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "Please supply string and currapt size\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    char *msg = argv[1];
    char currupt_size = *((char *)argv[2]) - '0';

    CheckSum *cs_msg = checksum(msg, strlen(msg));

    char *cmsg = currapt_msg(msg, (int)currupt_size);
    CheckSum *cs_cmsg = checksum(cmsg, strlen(cmsg));

    printf("before:\t%s\t%x\t%x\n", msg, cs_msg->checksum_add, cs_msg->checksum_xor);
    printf("after:\t%s\t%x\t%x\n", cmsg, cs_cmsg->checksum_add, cs_cmsg->checksum_xor);

    free(cmsg);
    free(cs_msg);
    free(cs_cmsg);

    return EXIT_SUCCESS;
}


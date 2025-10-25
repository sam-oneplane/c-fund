#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h> // for variadic functions
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

// standart HTTP port
#define SERVER_PORT 8989
#define HTTP_SERVER_PORT 80
#define MAX_LINE 8192
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 100 // server listen to N connection
#define PATH_MAX 200
#define THREAD_POOL_SIZE 20


void err_n_die(const char *fmt, ...); //variadic function
char *bin2hex(const unsigned char *input, size_t len);

#endif
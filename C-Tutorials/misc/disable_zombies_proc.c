#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

void avoid_zombie() {

    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));

    sa.sa_handler = SIG_DFL; /*default handler SIGCHLD*/
    /* we can customize our own sa_handler to wait to proc child */
    sa.sa_flags = SA_NOCLDWAIT;

    sigaction(SIGCHLD, &sa, NULL);

}

int main(int argc, char **argv) {

    avoid_zombie();
    while(true) {
        if(fork() == 0) /*child*/ {
            printf("zobie child process! - (%d)\n", getpid());
            exit(EXIT_SUCCESS); // exit child proccess while loop
        }
        sleep(1);
    }
}
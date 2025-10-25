#include <sys/mman.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



int ismapped(void *p, int bytes) {
    if(p == NULL) return 0;

    /*create a pipe */
    int fd[2]; /*pipe file descriptor read end write end*/
    int valid = 1;

    pipe(fd);

    /* write to pipe just to check if errno == EFAULT 
       meaning that the pointer we try to write to pipe
       is pointing to an unmaped memory 
       writing from ptr p number of bytes */

    if (write(fd[1], p, bytes) < 0) {
        if(errno == EFAULT) 
            valid = 0;
    }
    /* clode the pipe */
    close(fd[0]);
    close(fd[1]);

    return valid;
}


void testptr(void *p, int bytes, char *name) {
    printf("%s\t%d\t%p\n", name, ismapped(p, bytes), p);
}

int main(int argc, char **argv) {

    int *junk = NULL;
    int *junk2 = (int *)((uintptr_t *)0x352342524a);
    int *p = malloc(50);
    int x = 5;
    int *px = &x;

    testptr(junk, 1, "junk");
    testptr(junk2, 1, "junk2");
    testptr(p, 50, "p");
    testptr(px, sizeof(int), "px");
    
    // *junk = 123;

    return 0;
}
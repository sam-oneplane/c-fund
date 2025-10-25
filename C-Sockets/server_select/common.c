#include "common.h"

void err_n_die(const char *fmt, ...) {

    int errno_save;
    va_list ap;

    errno_save = errno;

    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    if(errno_save != 0) {
        fprintf(stdout, "(errno=%d): %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }

    va_end(ap);
    exit(1);
}

int check(int exp, const char *msg) {
    if (exp == SOCKETERROR) {
        err_n_die(msg);
        exit(1);
    }
   return exp;
}


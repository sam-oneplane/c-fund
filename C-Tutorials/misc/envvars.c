#include <stdio.h>
#include <stdlib.h>

extern char **environ; // stdlib pointer to enviornment varaiables list

int main(int argc, char **argv, char **envp) {

    // 2 ways to set env var
    putenv("LANG=en_US.UTF-8");
    setenv("COLORTERM", "truecolor", 1);

    

    printf("ENVP: \n");
    for(int i = 0; envp[i] != NULL; i++) {
        printf("%d: %s\n", i, envp[i]);
    }
    printf("ENVIRON: \n");
    for(int i = 0; environ[i] != NULL; i++) {
        printf("%d: %s\n", i, environ[i]);
    }

    printf("LANG: %s\nCOLORTERM: %s\n", getenv("LANG"), getenv("COLORTERM"));
}
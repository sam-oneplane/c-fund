#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


const char path[] = "/home/avivi/Developer/C/C11/C-tutorials/test_files/requirements.txt";
#define CAPCITY 50
    

char *get_with_realloc(FILE *stream) {
    int bytes = 0 ;
    char *buff = NULL;
    char c ;
    

    while ((c = fgetc(stream)) != EOF && c != '\r' && c != '\n' ) {
        bytes++ ;
        buff = realloc(buff, bytes+1);
        if (buff == NULL)
            return NULL;
        buff[bytes-1] = c ;
    }
    // in case of \r\n
    if(c == '\r') {
        c = fgetc(stream);
        if (c != '\n')
            ungetc(c, stream);
    }

    // check if empty buff
    if(buff == NULL) {
        if (c == EOF)
            return NULL;
        else
            buff = malloc(1); // something to return
    }
    // null termine buff
    buff[bytes] = 0;

    return buff;
}


char *get_with_capcity(FILE *stream) {
    int bytes = 0 ;
    int cap = CAPCITY;

    char *buff = (char *)malloc(cap);
    char c ;

    while((c = fgetc(stream)) != EOF && c != '\r' && c != '\n' ) {
        bytes++ ;
        // realloc only when you get to buff capaciity.
        if (bytes >= cap) {
            cap *= 2;
            buff = (char *)realloc(buff, cap);
            if (buff == NULL)
                return NULL;
        }
        buff[bytes-1] = c ;
    }
    // in case of \r\n
    if(c == '\r') {
        c = fgetc(stream);
        if (c != '\n')
            ungetc(c, stream);
    }

    // check if empty bytes
    if (bytes == 0) {
        if (c == EOF) {
            free(buff); // we have to free alloc buff with sizeof cap
            return NULL;
        }
        else
            buff = (char *)malloc(1); // something to return
    }
    // null termine buff
    buff[bytes] = 0;
    return buff;
}


void gen_lines_with_index() {

    
    char *str;
    int16_t linenum = 0;
    
    FILE *stream = fopen(path, "r");

    while((str = get_with_capcity(stream)) != NULL) {
        printf("%d--\t%s\n", linenum++, str);
        free(str); // have to relese allocated string from heap 
    }
}

int main() {

    gen_lines_with_index();
    return 0;
}
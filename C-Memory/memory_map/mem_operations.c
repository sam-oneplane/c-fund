#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>

#define MEM_SIZE 50
#define OFFSET 100
#define BUFF_SIZE 4092

typedef struct {
    char name[30];
    uint8_t age;
    uint8_t hight;
    uint8_t weight;
}Person;

// long sysconf(int name);

int main(void) {

    // malloc calloc realloc and free
    int *mem = malloc(sizeof(int)* MEM_SIZE );
    *(mem+10) = 90;
    // alloc with initiation to zeros
    int *zeroes = calloc(sizeof(int), MEM_SIZE );
    // mem can get a different pointer value due to realloc 
    mem = realloc(mem, sizeof(int)* MEM_SIZE*2) ;

    printf("%d\n", mem[10]);
    free(mem);
    free(zeroes);

    void *mymem = malloc(MEM_SIZE);
    uint8_t *ptr = (uint8_t *)mymem;
    ptr[2] = 0x1e;

    printf("%d\n", ptr[2]);
    free(mymem);


    // static initialization on stack
    Person pst = {.name = "Samuel Mashiach", .age=55, .hight=190, .weight=90};

    // dynamic initialization
    Person *p = (Person *)malloc(sizeof(Person));
    // copy a struct
    memcpy(p, &pst, sizeof(Person));
    printf("%s\n", p->name);
    strncpy(p->name, "Sam Mash", strlen("Sam Mash")+1);
    printf("%s\n", p->name);


    /* memset buffer and memcpy struct to buffer */
    char buff[BUFF_SIZE];
    /* set buff to 0 values */
    memset(buff, 0, BUFF_SIZE);
    memcpy(buff+OFFSET, p, sizeof(Person));
    /* cast buff pointer into struct person ptr */
    Person *p1 = (Person *)(buff+OFFSET);
    printf("%s\n", p1->name);
    free(p);
    /*
    zeroes = NULL;
    mem = NULL;
    p = NULL;
    */

    /* MEMORY ALIGN*/
    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1)
        perror("sysconf");
    
    int buffsize = 2*pagesize;

    char *ptr0 = malloc(sizeof(char) * 50);
    char *ptr1, *ptr2;
    // alloc memory which is align to page size return 0 on SUCCESS
    if(posix_memalign((void **)&ptr1, pagesize, buffsize))
        perror("memalign");

    // OR use mmap to align pages
    ptr2 = (char *)mmap(NULL, buffsize, PROT_READ | PROT_WRITE,  MAP_PRIVATE, -1, 0);
    if(ptr2 == MAP_FAILED)
        perror("mmap");

    printf("ptr0: addr %p\n", ptr0);
    printf("ptr1: addr %p\n", ptr1);

    memset(ptr1, 8, buffsize);
    printf("memory @ base addr+2 is %d\n",*(ptr1 + 2));

    memset(ptr1+pagesize, 3, pagesize-1);
    // create addr ptr1 + pagesize READ_ONLY
    if(mprotect(ptr1+pagesize, pagesize, PROT_READ) == -1)
        perror("mprotect");
    // test if can read 
    printf("memory @ baseaddr+pagesize+2 is %d\n",*(ptr1 + pagesize + 2));
    return EXIT_SUCCESS;
    
}
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>


#define MOD_STEP 3

// move data from disk to ram using mmap 
int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1; // Exit if no path is provided
    }

    // The file path is in argv[1]
    char *file_path = argv[1];
    /* use program break to increment heap memory
    intptr_t inc = 4096;
    void *current_brk = sbrk(inc);
    printf("current break: %p\n", current_brk);
    USE mmap insted */
    
    int fd = open(file_path, O_RDWR, S_IRUSR | S_IWUSR);
    struct stat sb;

    if(fstat(fd, &sb) == -1) {
        perror("couldn't open the file");
    }
    printf("file size : %ld\n", sb.st_size);

    /* request block of aligned memory page 
    uint8_t *block = mmap(NULL, 4096,  PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    */
    // memory map file pointer to block of memory
    char *file_in_mem = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); //MAP_PRIVATE
    /*
        return pointer to block of memory
        0 is the offset
        sb.st_size the size 
    */

    for (int i = 0 ; i < sb.st_size ; i++) {
        if((i%MOD_STEP) == 0) {
            file_in_mem[i] = toupper(file_in_mem[i]);
        }
        printf("%c", file_in_mem[i]);
    }
    printf("\n");
    
    return 0;
}
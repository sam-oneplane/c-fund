#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    
    int fd = open("../test_files/librosa_vocal_analizer.py", O_RDWR, S_IRUSR | S_IWUSR);
    struct stat sb;

    if(fstat(fd, &sb) == -1) {
        perror("couldn't open the file");
    }
    printf("file size : %lld\n", sb.st_size);

    char *file_in_mem = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); //MAP_PRIVATE
    /*
        return pointer to block of memory 
        0 is the offset
        sb.st_size the size 
    */

    for (int i = 0 ; i < sb.st_size ; i++) {
        if((i%2) == 0) {
            file_in_mem[i] = toupper(file_in_mem[i]);
        }
        printf("%c", file_in_mem[i]);
    }
    printf("\n");
    
    return 0;
}
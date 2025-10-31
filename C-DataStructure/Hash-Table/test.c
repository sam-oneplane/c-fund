#include "hashtable.h"

#define TABLESIZE (1 << 10)

int main(int argc, char **argv) {

    if(argc != 2) {
        printf("usage: <test wordlist-filename>\n");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];

    hash_table *htable = create(hash, TABLESIZE); 

    FILE *fp = fopen(filename, "r");
    char buffer[MAXLINE];
    uint32_t wordscntr = 0;
    while(!feof(fp) &&  fgets(buffer, MAXLINE, fp) != NULL) {
        buffer[strcspn(buffer, "\n\r")] = 0;            // replace \n or \r with 0 in buffer
        char *newentry = malloc(strlen(buffer) + 1);    // create new entry in heap
        strcpy(newentry, buffer);                       // copy buffer to newentry heap memory location
        insert(htable, newentry, newentry);             // key and obj are the same
        wordscntr++;
        free(newentry);
    }
    fclose(fp);

    printf("load %d number of words to hash table\n",wordscntr);
    
    const char *key = "starlette==0.46.2";
    void *res = delete_entry(htable, key);
   
    if (res != NULL)
        printf("delete entry of %s(%p)\n", key, res);

    print_hash(htable);
        
    destroy(htable);  
}
#include "hashtable.h"

#define MAX_LINE 4096

uint64_t hash(const char *key, size_t length) {
    uint64_t hash_value = 0;
    for (int i=0; i < length; i++) {
        hash_value += key[i];
        hash_value = hash_value * key[i];
    }
    return hash_value;
}

int main(int argc, char **argv) {

    if(argc != 2) {
        printf("usage: <wordlist filename>\n");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];

    const int tablesize = (1 << 10);
    hash_table *htable = create(tablesize, hash); 

    FILE *fp = fopen(filename, "r");
    char buffer[MAX_LINE];
    uint32_t wordscntr = 0;
    while(!feof(fp) &&  fgets(buffer, MAX_LINE, fp) != NULL) {
        buffer[strcspn(buffer, "\n\r")] = 0; // replace /n or /r with 0
        char *newentry = malloc(strlen(buffer) + 1); // create new entry in heap
        strcpy(newentry, buffer);
        insert(htable, newentry, newentry); // key and obj are the same
        wordscntr++;
    }
    fclose(fp);
    printf("load %d number of words to hash table\n",wordscntr);
    print_hash(htable);
    destroy(htable);  
}
#include "hashtable.h"

/* this is beacuase hash function can preduce same key to different entries */
typedef struct entry 
{
    char *key;
    void *obj;
    struct entry *next;
    
} entry;

typedef struct hash_table
{
    uint32_t size;
    hashfunction hashf;
    entry **elements; // *element[TABLESIZE] array of pointers to entries
} hash_table;


uint64_t hash(const char *key, uint32_t size) {
    int length = (int)strnlen(key, MAXLINE);
    uint64_t hash_value = 0;
    for (int i=0; i < length; i++) {
        hash_value += key[i];
        hash_value = (hash_value * key[i]) % size;
    }
    return hash_value;
}

hash_table *create(hashfunction hf, uint32_t size) {
    hash_table *ht = malloc(sizeof(hash_table));
    ht->hashf = hf;
    ht->size = size;
    // calloc zero out the memory allocated : TABLESIZE array of entry pointers
    ht->elements = calloc(sizeof(entry*), size);
    return ht;
}

void destroy(hash_table *ht) {
    free(ht->elements);
    free(ht);
    ht = NULL;
}

void print_hash(hash_table *ht) {
    for(uint32_t i=0; i < ht->size; i++) {
        if(ht->elements[i] != NULL) {
            entry *tmp = ht->elements[i];
            printf(" entry %i -->\n",i);
            while(tmp != NULL) {
                printf("\t%s(%p)\n", tmp->key, tmp->obj);
                tmp = tmp->next;
            }
        }
    }
}

bool insert(hash_table *ht, const char *key, void *obj) {
    if(key == NULL || obj == NULL) return false;
    size_t indx = ht->hashf(key, ht->size);

    if(lookup(ht, key) != NULL) return false;

    entry *e = malloc(sizeof(entry));
    e->obj = obj;
    e->key = malloc(strlen(key) + 1);
    strcpy(e->key, key);
    // insert to head of hash table
    e->next = ht->elements[indx];
    // table entry ptr points to new entry 
    ht->elements[indx] = e;

    return true;
}

void *lookup(hash_table *ht, const char *key) {
    if(key == NULL || ht == NULL) return NULL;
    size_t indx = ht->hashf(key, ht->size);

    entry *tmp = ht->elements[indx];
    while (tmp != NULL && strcmp(key, tmp->key) != 0) tmp = tmp->next;
    if (tmp == NULL) return NULL;
    return tmp->obj;
}

void *delete_entry(hash_table *ht, const char *key) {
    if(key == NULL || ht == NULL) return NULL;
    uint64_t indx = ht->hashf(key, ht->size);

    entry *tmp = ht->elements[indx];
    if (tmp == NULL) return NULL;
    
    entry *prev = NULL;
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    
    if (prev == NULL) { // head of the list
        ht->elements[indx] = tmp->next; 
    }else {
        prev->next = tmp->next;
    }
    void *obj = tmp->obj;
    free(tmp);
    return obj; 
}
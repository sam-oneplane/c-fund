#include "hashtable.h"


typedef struct entry 
{
    char *key;
    void *obj;
    struct entry *next;
    
} entry;

typedef struct _hash_table
{
    uint32_t size;
    hashfunction *hashf;
    entry **elements;
} hash_table;

// private
static size_t ht_index(hash_table *ht, const char *key) {
    size_t result = ht->hashf(key, strlen(key)) % ht->size;
    return result;
}

hash_table *create(uint32_t size, hashfunction *hf) {
    hash_table *ht = malloc(sizeof(hash_table));
    ht->size = size;
    ht->hashf = hf;
    // calloc zero out the memory allocated
    ht->elements = calloc(sizeof(entry*), ht->size);
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
            printf("\t%i\t-->\n",i);
            while(tmp != NULL) {
                printf("%s\t(%p)\n", tmp->key, tmp->obj);
                tmp = tmp->next;
            }
        }
    }
}

bool insert(hash_table *ht, const char *key, void *obj) {
    if(key == NULL || obj == NULL) return false;
    size_t indx = ht_index(ht, key);

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
    size_t indx = ht_index(ht, key);

    entry *tmp = ht->elements[indx];
    while (tmp != NULL && strcmp(key, tmp->key) != 0) tmp = tmp->next;
    if (tmp == NULL) return NULL;
    return tmp->obj;
}

void *delete_entry(hash_table *ht, const char *key) {
    if(key == NULL || ht == NULL) return NULL;
    size_t indx = ht_index(ht, key);

    entry *tmp = ht->elements[indx];
    entry *prev = ht->elements[indx];
    while (tmp != NULL && strcmp(key, tmp->key) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    prev->next = tmp->next;
    void *obj = tmp->obj;
    free(tmp);
    return obj;
}
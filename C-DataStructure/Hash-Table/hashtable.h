#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct _hash_table hash_table; 
typedef uint64_t (hashfunction) (const char *, size_t);

hash_table *create(uint32_t size, hashfunction *hfunc);
void destroy(hash_table *);
void print_hash(hash_table *);
bool insert(hash_table *ht, const char *key, void *obj);
void *lookup(hash_table *ht, const char *key);
void *delete_entry(hash_table *ht, const char *key);

#endif
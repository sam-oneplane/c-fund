#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define _GNU_SOURCE

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define MAXLINE 256

typedef struct hash_table hash_table; 
typedef uint64_t (*hashfunction) (const char *, uint32_t);

uint64_t hash(const char *key, uint32_t size) ;
hash_table *create(hashfunction hfunc, uint32_t size);
void destroy(hash_table *);
void print_hash(hash_table *);
bool insert(hash_table *ht, const char *key, void *obj);
void *lookup(hash_table *ht, const char *key);
void *delete_entry(hash_table *ht, const char *key);

#endif
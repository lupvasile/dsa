#ifndef HASH_OPEN_H_INCLUDED
#define HASH_OPEN_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct hash_open HashOpenT;
typedef struct hash_open
{
    int size;
    void *(*extractKey)(void *pData);
    int (*compareKeys)(void *pKey1, void *pKey2);
    void (*printData)(void *pData);
    int (*hash)(void *pKey, int step);
    void **table;

    int (*find)(HashOpenT *H, void *pKey);///returns position of given key in hash table if found, returns H->size if not found
    void (*delete)(HashOpenT *H, void *pKey);
    int (*insert)(HashOpenT *H, void *pData);///returns 1 on success, 0 on failure
    void (*print)(HashOpenT *H, FILE *fout);///prints hash Table contents in file

}HashOpenT;

HashOpenT *createHashTable(int size,void *(*extractKey)(void *), int (*compareKeys)(void *, void *), void (*printData)(void *), int (*hash)(void*, int));
#endif // HASH_CHAIN_H_INCLUDED

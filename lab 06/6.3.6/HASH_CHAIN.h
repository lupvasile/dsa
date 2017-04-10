#ifndef HASH_CHAIN_H_INCLUDED
#define HASH_CHAIN_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct hash_list_entry
{
    void *pData;
    struct hash_list_entry *next;
} HashEntryT;

typedef struct hash_chain HashChainT;
typedef struct hash_chain
{
    int size;
    void *(*extractKey)(void *pData);
    int (*compareKeys)(void *pKey1, void *pKey2);
    void (*printData)(void *pData);
    int (*hash)(void *pKey);
    HashEntryT **table;

    HashEntryT *(*find)(HashChainT *H, void *pKey);///returns pointer to HashEntryT if found element with given key, NULL otherwise
    HashEntryT *(*delete)(HashChainT *H, void *pKey);///returns pointer to deleted entry
    void (*insert)(HashChainT *H, void *pData);
    void (*print)(HashChainT *H, FILE *fout);///prints hash Table contents in file
}HashChainT;

HashChainT *createHashTable(int size,void *(*extractKey)(void *), int (*compareKeys)(void *, void *), void (*printData)(void *), int (*hash)(void*));
#endif // HASH_CHAIN_H_INCLUDED

#include "HASH_CHAIN.h"

static HashEntryT *createHashEntry(void *pData)
{
    HashEntryT *p = malloc(sizeof(HashEntryT));
    p->pData = pData;
    p->next = NULL;

    return p;
}

static void insertHashChain(HashChainT *H, void *pData)
{
    int hsh = H->hash(H->extractKey(pData));

    HashEntryT *ptr = createHashEntry(pData);
    ptr->next = H->table[hsh];
    H->table[hsh] = ptr;
}

static HashEntryT *deleteHashChain(HashChainT *H, void *pKey)
{
    int hsh = H->hash(pKey);

    HashEntryT *ptr = H->table[hsh], *antPtr = NULL;

    for(;ptr != NULL; ptr = ptr->next){
        if(H->compareKeys(pKey,H->extractKey(ptr->pData)) == 0) break;
        antPtr = ptr;
    }

    if(ptr == NULL) return NULL;
    if(antPtr == NULL)
    {
        H->table[hsh] = H->table[hsh]->next;
        return ptr;
    }

    antPtr->next = ptr->next;
    return ptr;

}


static HashEntryT *findHashChain(HashChainT *H, void *pKey)
{
    int hsh = H->hash(pKey);

    HashEntryT *ptr = H->table[hsh];
    for(;ptr != NULL; ptr = ptr->next)
        if(H->compareKeys(pKey,H->extractKey(ptr->pData)) == 0) return ptr;

    return NULL;
}

static void printHashChain(HashChainT *H, FILE *fout)
{
    int ok = 0;
    for(int i = 0; i < H->size; ++i)
        if(H->table[i] != NULL)
    {
        fprintf(fout, "Bucket for hash value %d\n",i);
        HashEntryT *ptr = H->table[i];
        for(;ptr != NULL; ptr = ptr->next)
        {
            fprintf(fout,"\t");
            H->printData(ptr->pData);
            fprintf(fout,"\n");
        }
        ok = 1;
    }

    if(!ok) fprintf(fout,"no elements\n");
}

HashChainT *createHashTable(int size,void *(*extractKey)(void *), int (*compareKeys)(void *, void *), void (*printData)(void *), int (*hash)(void*))
{
    HashChainT *ptrH = malloc(sizeof(HashChainT));

    if(ptrH == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

    ptrH->compareKeys = compareKeys;
    ptrH->extractKey = extractKey;
    ptrH->hash = hash;
    ptrH->printData = printData;
    ptrH->size = size;

    ptrH->table = malloc(sizeof(HashEntryT *) * size);
    if(ptrH->table == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

    for(int i = 0; i < size; ++i)
        ptrH->table[i] = NULL;

    ptrH->find = findHashChain;
    ptrH->insert = insertHashChain;
    ptrH->delete = deleteHashChain;
    ptrH->print = printHashChain;

    return ptrH;
}

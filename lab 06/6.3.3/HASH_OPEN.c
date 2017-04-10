#include "HASH_OPEN.h"


static int insertHashOpen(HashOpenT *H, void *pData)
{
    int hsh;
    for(int i = 0; i < H->size; ++i)
    {
        hsh = H->hash(H->extractKey(pData),i);
        if (H->table[hsh] == NULL)
        {
            H->table[hsh] = pData;
            return 1;
        }
    }

    return 0;
}

static int findHashOpen(HashOpenT *H, void *pKey)
{
    int hsh;
    for(int i = 0; i < H->size; ++i)
    {
        hsh = H->hash(pKey,i);
        if(H->table[hsh] == NULL) continue;
        if(H->compareKeys(pKey, H->extractKey(H->table[hsh])) == 0) return hsh;
    }

    return H->size;
}

static void deleteHashOpen(HashOpenT *H, void *pKey)
{
    int hsh = findHashOpen(H,pKey);

    if(hsh == H->size) return;
    H->table[hsh] = NULL;
}



static void printHashOpen(HashOpenT *H, FILE *fout)
{
    int ok = 0;
    for(int i = 0; i < H->size; ++i)
        if(H->table[i] != NULL)
        {
            fprintf(fout, "Bucket for hash value %d\n",i);
                fprintf(fout,"\t");
                H->printData(H->table[i]);
                fprintf(fout,"\n");
                ok = 1;
        }

    if(!ok) fprintf(fout,"no elements\n");
}

HashOpenT *createHashTable(int size,void *(*extractKey)(void *), int (*compareKeys)(void *, void *), void (*printData)(void *), int (*hash)(void*, int))
{
    HashOpenT *ptrH = malloc(sizeof(HashOpenT));

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

    ptrH->table = malloc(sizeof(void *) * size);
    if(ptrH->table == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

    for(int i = 0; i < size; ++i)
        ptrH->table[i] = NULL;

    ptrH->find = findHashOpen;
    ptrH->insert = insertHashOpen;
    ptrH->delete = deleteHashOpen;
    ptrH->print = printHashOpen;

    return ptrH;
}

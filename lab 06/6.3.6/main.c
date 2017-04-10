#include <stdio.h>
#include <string.h>
#include "HASH_CHAIN.h"
#include "TEST.h"

#define SIZE 2909

FILE *openCheck(const char *name,const char *mode)
{
    FILE *f = fopen(name,mode);
    if(f == NULL)
    {
        perror("");
        exit(1);
    }

    return f;
}

FILE *fin,*fout;


int compare(void *key1, void *key2)
{
    return *(long*)key1 - *(long*)key2;
}

void print(void *item)
{
    fprintf(fout,"%d",*(long*)item);
}

void *extract(void *item)
{
    return item;
}

///not working find and delete
int hashMemory(void *pKey)
{
    return (int)pKey % SIZE;
}

int hashInteger(void *pKey)
{
    return *((long*)pKey) % SIZE;
}

int hashComponent(void *pKey)
{
    short *sh = pKey;
    return (*sh + *(sh+1))%SIZE;
}

long *allocLong(long x)
{
    long *p = malloc(sizeof(long));
    if(p == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

    *p = x;
    return p;
}


int main(int argc,char* argv[])
{

    fin = openCheck(argv[1],"w");
    makeTest(fin);///currently nr_entry is 1e4
    fclose(fin);


    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    printf("enter 1 for memory address\n2 for integer cast\n3 for component sum\n");
    int mod;
    scanf("%d",&mod);

    HashChainT *H = NULL;

    if(mod == 1) H = createHashTable(SIZE,extract,compare,print,hashMemory);
    if(mod == 2) H = createHashTable(SIZE,extract,compare,print,hashInteger);
    if(mod == 3) H = createHashTable(SIZE,extract,compare,print,hashComponent);

    char op;
    while ((op = fgetc(fin)) != EOF)
    {
        long val;
        fscanf(fin,"%d",&val);


        switch (op)
        {
        case 'i':
        {
            long *ptr = allocLong(val);
            H->insert(H, ptr);
            break;
        }
        case 'd':
            H->delete(H,&val);
            break;
        case 'f':
            if(H->find(H,&val) != NULL) fprintf(fout,"yes %d\n",H->hash(&val));
            else fprintf(fout,"no\n");
            break;

        case 'l':
            H->print(H,fout);
            break;
        }
    }


    fclose(fin);
    fclose(fout);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include "HASH_OPEN.h"
#include "TEST.h"

#define SIZE ((int)nr_entry - 2)

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
    fprintf(fout,"%d",*(int*)item);
}

void *extract(void *item)
{
    return item;
}

/**
the hash value is computed as follows:
    key modulo mod
**/
int hash(void *pKey,int mod)
{
    return *((long*)pKey) % mod;
}

//this hash function uses linear probing for solving collisions
int hashLinear(void *pKey, int step)
{
    static int res = 0;

    if(step == 0) res = hash(pKey,SIZE);
    return (res+step)%SIZE;
}

//this hash function uses quadratic probing for solving collisions
int hashQuadratic(void *pKey, int step)
{
    static int res = 0;

    if(step == 0) res = hash(pKey,SIZE);
    return (res+step+1ll*2*step*step)%SIZE;
}

//this hash function uses double hashing for solving collisions
int hashDouble(void *pKey,int step)
{
    static int res = 0;
    static int hsh2 = 0;
    if(step == 0) res = hash(pKey,SIZE);
    if(step == 1) hsh2 = hash(pKey,666013);
    return (res+1ll*step*hsh2)%SIZE;
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

    printf("enter 1 for linear probing\n2 for quadratic probing\n3 for double hashing\n");
    int mod;
    scanf("%d",&mod);

    HashOpenT *H = NULL;

    if(mod == 1) H = createHashTable(SIZE,extract,compare,print,hashLinear);
    if(mod == 2) H = createHashTable(SIZE,extract,compare,print,hashQuadratic);
    if(mod == 3) H = createHashTable(SIZE,extract,compare,print,hashDouble);

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
            if(!H->insert(H, ptr)) fprintf(fout,"not enough space for %d\n",val);
            break;
        }
        case 'd':
            H->delete(H,&val);
            break;
        case 'f':
        {
            int x = H->find(H,&val);
            if(x != H->size) fprintf(fout,"yes %d\n",x);
            else fprintf(fout,"no\n");
            break;
        }

        case 'l':
            H->print(H,fout);
            break;
        }
    }


    fclose(fin);
    fclose(fout);

    return 0;
}

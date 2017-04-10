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

int getMaxLen(FILE *f)
{
    char ch;
    int maxLen = 0, currLen = 0;

    while(1)
    {
        ch = getc(f);
        if(ch == EOF || ch == '\n')
        {
            if(currLen > maxLen) maxLen = currLen;
            currLen = 0;

            if(ch == EOF) break;
            continue;
        }

        currLen++;
    }

    rewind(f);
    return maxLen;
}


int compare(void *key1, void *key2)
{
    return strcmp((char*)key1,(char*)key2);
}

void print(void *item)
{
    fprintf(fout,"%s",(char*)item);
}

void *extract(void *item)
{
    return item;
}


/**
this hash function uses linear probing for solving collisions
the initial hash value is computed as follows:
    the characters of the key are considered coefficients of a polinom of degree strlen(key)-1
    computed at x = BASE
    the polinom value is calculated modulo SIZE

i chose this function because it generates fewer collisions
**/
int hash(void *pKey, int step)
{
    int BASE = 250;
    static int res = 0;

    if(step == 0)
    {
        char *s = (char*) pKey;
        for(; *s; ++s)
            res = (res * BASE + *s) % SIZE;
    }
    return (res+step)%SIZE;
}

int main(int argc,char* argv[])
{
    fin = openCheck(argv[1],"w");
    makeTest(fin);///currently nr_entry is 1e4
    fclose(fin);


    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");


    HashOpenT *H = createHashTable(SIZE,extract,compare,print,hash);

    int bufLen = getMaxLen(fin)+2;
    char buf[bufLen];

    while (fgets(buf,sizeof buf,fin))
    {
        buf[strlen(buf)-1] = '\0';

        switch (buf[0])
        {
        case 'i':
        {
            if(!H->insert(H, strdup(buf+1))) fprintf(fout,"not enough space for %s\n",buf+1);
            break;
        }
        case 'd':
            H->delete(H,extract(buf+1));
            break;
        case 'f':
        {
            int x = H->find(H,extract(buf+1));
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

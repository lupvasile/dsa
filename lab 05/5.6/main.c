#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

FILE *fin,*fout;

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

int compare(void *key1, void *key2)
{
    return strcmp((char*)key1, (char*)key2);
}

void *extract(void *it)
{
    return it;
}

void print(void *item)
{
    fprintf(fout,"%s ",(char*)item);
}

void makeTree(BST_Tree *T)
{
#define bufLen 1024
    char buf[bufLen];

    int nr;
    fscanf(fin,"%d",&nr);
    for(int i = 0; i<nr; ++i)
    {
        fscanf(fin,"%s",buf);
        insertBST(T,strdup(buf));
    }
}

int main(int argc,char* argv[])
{
    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    BST_Tree *T1 = createBstTree(compare,extract,print);
    BST_Tree *T2 = createBstTree(compare,extract,print);

    makeTree(T1);
    makeTree(T2);

    BST_Tree *T_Merged = createBstTree(compare,extract,print);
    mergeTree(T_Merged,T1,T2);

    inBST(T_Merged);

    fclose(fin);
    fclose(fout);
    return 0;
}

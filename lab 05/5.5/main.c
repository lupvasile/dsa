#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "BST.h"

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
        if(ch == EOF || isspace(ch))
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

int main(int argc,char* argv[])
{
    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    BST_Tree *T = createBstTree(compare,extract,print);

    int bufLen = getMaxLen(fin)+2;
    char buf[bufLen];

    while (fscanf(fin,"%s",buf)!=EOF)
    {
        insertBST(T,strdup(buf));
    }

    inBST(T,fout);

    fclose(fin);
    fclose(fout);

    return 0;
}

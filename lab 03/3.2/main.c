#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <ctype.h>

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

///returns max length of a word
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

int main(int argc,char* argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

    int bufLen = 1024;
    bufLen = getMaxLen(fin)+2;

    ListT *ptrList = createList();

    char buf[bufLen];
    while(fscanf(fin,"%s",buf) != EOF)
            insertInOrder(ptrList,buf);

    printList(fout,ptrList,'\n');
    fprintf(fout,"\n");
    printRevList(fout,ptrList,'\n');

    fclose(fin);
    fclose(fout);
    return 0;
}

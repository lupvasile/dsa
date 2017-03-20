#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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


int main(int argc,char* argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

    int bufLen = 1024;
    //bufLen = getMaxLen(fin);

    ListT *ptrList = createList();

    char buf[bufLen];
    while(fscanf(fin,"%s",buf) != EOF)
            insertInOrder(ptrList,buf);

    printList(stdout,ptrList,'\n');

    fclose(fin);
    fclose(fout);
    return 0;
}

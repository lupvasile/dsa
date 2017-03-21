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

    ListT *ptrList = createList();

    int x;
    while(fscanf(fin,"%d", &x) != EOF)
        insertAtFront(ptrList,createNode(x));

    printList(fout,ptrList,' ');

    fclose(fin);
    fclose(fout);
    return 0;
}

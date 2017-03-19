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

int main(int argc,char *argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

    ListT *ptrList = createList();

    int nrKids, i, offset;
    fscanf(fin,"%d", &nrKids);

    for(i = 1; i <= nrKids; ++i)
    {
        char buf[2014];
        fscanf(fin,"%s",buf);

        NodeT *ptr = createNode(buf);
        insertAtRear(ptrList,ptr);
    }

    while(ptrList->count > 1)
    {
        offset = (nrKids-1) % ptrList->count;///faster implementation
        for(i = 1; i <= offset; ++i)
            ptrList->first = ptrList->first->next;

        deleteFirst(ptrList);///ptrList will be on number one
    }

    printList(fout,ptrList,0);

    return 0;
}

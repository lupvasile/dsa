#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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


int main(int argc,char *argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

    ListT *ptrList = createList();

    int nrKids, i, offset, nrCount;
    int bufLen = getMaxLen(fin)+2;
    char buf[bufLen];

    fscanf(fin,"%d%d", &nrKids, &nrCount);


    for(i = 1; i <= nrKids; ++i)
    {
        fscanf(fin,"%s",buf);

        NodeT *ptr = createNode(buf);
        insertAtRear(ptrList,ptr);
    }

    printf("give starting kid:\n");
    scanf("%s",buf);
    NodeT *nodePtr;

    while((nodePtr = find(ptrList,buf))==NULL)
    {
        printf("%s not found\ngive starting kid:\n",buf);
        scanf("%s",buf);
    }

    while(ptrList->count > 1)
    {
        offset = (nrCount-1) % ptrList->count;///faster implementation
        for(i = 1; i <= offset; ++i)
        {
            nodePtr = nodePtr->next;
            if(nodePtr == ptrList->first) nodePtr = nodePtr->next;
        }

        deleteAtIndex(ptrList,nodePtr);
    }

    printList(fout,ptrList,0);

    fclose(fin);
    fclose(fout);
    return 0;
}

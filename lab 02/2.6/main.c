#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define nmax 28

ListT *G[nmax];
int viz[nmax];

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

void dfs(int nod,ListT *res)
{
    viz[nod] = 1;

    for(NodeT *ptr = G[nod]; ptr; ptr = ptr->next)
        if(!viz[ptr->key]) dfs(ptr->key,res);

    insertAtFront(res,createNode(nod));
}

void init()
{
    int i;
    for(i = 0; i < nmax; ++i) G[i] = createList(),viz[i] = 1;
}

void printCharList(FILE *f, ListT *ptrList)
{
    if(isEmpty(ptrList)) fprintf(f,"none");
    else
    {
        NodeT *nodePtr = ptrList->first;
        for(;nodePtr != NULL; nodePtr = nodePtr->next)
            fprintf(f,"%c ",nodePtr->key+'a');
    }

}


int main(int argc,char* argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

    init();

    char buf[4];
    while(fgets(buf,sizeof buf,fin))
    {
        int a,b;
        a = buf[0] - 'a';
        b = buf[2] - 'a';

        viz[a] = viz[b] = 0;
        insertAtFront(G[a],createNode(b));
    }

    ListT *ptrRes = createList();

    int i;
    for(i = 0;i < nmax; ++i)
        if(!viz[i]) dfs(i,ptrRes);

    printCharList(fout,ptrRes);
    return 0;
}

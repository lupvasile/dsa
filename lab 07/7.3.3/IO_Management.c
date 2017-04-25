#include "IO_Management.h"

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

int getNrNodes(FILE *fin, int *nrarcs)
{
    char buf[200];
    int max = -1;
    *nrarcs = 0;
    while(fgets(buf,sizeof buf,fin))
    {
        int x,y;
        sscanf(buf,"%d,%d",&x,&y);
        (*nrarcs)++;
        if(x>max) max = x;
        if(y>max) max = y;
    }
    rewind(fin);
    return max;
}



void readArcs(FILE *fin, int *nodes, int nrNodes, ListT *adj[], EdgeT arcs[])
{
    char buf[200];

    int i = 0;
    while(fgets(buf,sizeof buf,fin))
    {
        int node;
        sscanf(buf,"%d,%d=%d",&node,&arcs[i].node,&arcs[i].val);
        if(adj[node] == NULL) adj[node] = createList();
        insertAtFront(adj[node],createNode(&arcs[i]));
        ++i;
    }

}

int getMaxLen(FILE *f, char *delim)
{
    int maxLen = 0, currLen = 0;

    while(1)
    {
        char ch;
        ch = getc(f);
        if(ch == EOF || strchr(delim,ch) != NULL)
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

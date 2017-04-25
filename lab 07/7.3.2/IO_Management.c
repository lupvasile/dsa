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

int getNrNodes(FILE *fin)
{
    fpos_t pos;
    fgetpos(fin,&pos);

    fscanf(fin,"%*s nodes ");
    int nrNodes = 0;
    char buf[102];
    while(fscanf(fin,"%100s",buf) != EOF)
        {
            if(buf[0]>'9' || buf[0]<'0') break;
            ++nrNodes;
        }

    fsetpos(fin,&pos);
    return nrNodes;
}

int getNrArcs(FILE *fin)
{
    fpos_t pos;
    fgetpos(fin,&pos);

    fscanf(fin,"%*s arcs ");
    int nrArcs = 0;
    char buf[102];
    while(fscanf(fin,"%100s",buf) != EOF)
        {
            if(buf[0]!='(' && buf[strlen(buf)-1] != ')') break;
            ++nrArcs;
        }

    fsetpos(fin,&pos);
    return nrArcs/2;
}

void readNodes(FILE *fin,char *name, int *nodes, int nrNodes)
{
    fscanf(fin,"%s nodes",name);
    for(int i = 0; i < nrNodes; ++i) fscanf(fin,"%d",nodes+i);
}

int binSrc(int a[],int n, int val)
{
   int step,pos = 0;
   for(step = 1; step <= n; step<<=1);
   step>>=1;
   for(;step;step>>=1)
    if(pos+step<=n)
        if(a[pos+step] <= val) pos+=step;

   return pos;
}

void readArcsNormalised(FILE *fin, int *nodes, int nrNodes, ListT *adj[], int nrArcs)
{
    fscanf(fin,"%*s arcs");

    int x,y;

    for(int i = 0; i < nrArcs; ++i)
    {
        fscanf(fin," (%d %d)",&x,&y);
        x = binSrc(nodes,nrNodes-1,x);
        y = binSrc(nodes,nrNodes-1,y);

        if(adj[x] == NULL) adj[x] = createList();
        insertAtFront(adj[x],createNode(y));
    }

}
void readArcsNormalisedMat(FILE *fin, int *nodes, int nrNodes, char adj[nrNodes][nrNodes], int nrArcs)
{
    fscanf(fin,"%*s arcs");

    int x,y;

    for(int i = 0; i < nrArcs; ++i)
    {
        fscanf(fin," (%d %d)",&x,&y);
        x = binSrc(nodes,nrNodes-1,x);
        y = binSrc(nodes,nrNodes-1,y);

        adj[x][y] = adj[y][x] = 1;
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

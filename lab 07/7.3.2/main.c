#include <stdio.h>
#include <string.h>
#include "TEST.h"
#include "IO_Management.h"
#include "list.h"

FILE *fin,*fout;

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


void dfs(int node, int nrNodes, char adj[nrNodes][nrNodes], char used[],int nodes[])
{
    used[node] = 1;
    fprintf(fout,"%d ",nodes[node]);

    for(int i = 0; i < nrNodes; ++i)
        if(!used[i] && adj[node][i])
            dfs(i,nrNodes,adj,used,nodes);
}

void dfs_traversal(int nrNodes,char adj[nrNodes][nrNodes],int nodes[])
{
    char used[nrNodes];
    memset(used,0,sizeof used);

    for(int i = 0; i < nrNodes; ++i)
        if(!used[i]) dfs(i,nrNodes,adj,used,nodes);
}


void bfs(int node, int nrNodes, char adj[nrNodes][nrNodes], char used[],int nodes[])
{

    ListT *queue = createList();
    insertAtRear(queue,createNode(node));

    used[node] = 1;

    while(!isEmpty(queue))
    {
        node = queue->first->key;
        deleteFirst(queue);

        fprintf(fout,"%d ",nodes[node]);

        for(int i = 0; i < nrNodes; ++i)
            if(!used[i] && adj[node][i])
            {
                insertAtRear(queue,createNode(i));
                used[i] = 1;
            }
    }
}


void bfs_traversal(int nrNodes,char adj[nrNodes][nrNodes],int nodes[])
{
    char used[nrNodes];
    memset(used,0,sizeof used);

    for(int i = 0; i < nrNodes; ++i)
        if(!used[i]) bfs(i,nrNodes,adj,used,nodes);
}


int main(int argc,char* argv[])
{
    fin = openCheck(argv[1],"w");
    makeTest(fin);///currently nr_nodes and nr_arcs is 1e3
    fclose(fin);

    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    int nrNodes = getNrNodes(fin);
    int nodes[nrNodes];
    int bufLen = getMaxLen(fin," \n");
    char graphName[bufLen];

    readNodes(fin,graphName,nodes,nrNodes);
    qsort(nodes,nrNodes,sizeof(nodes[0]),cmp);

    char adjMatrix[nrNodes][nrNodes];
    memset(adjMatrix,0,sizeof adjMatrix);

    int nrArcs = getNrArcs(fin);
    readArcsNormalisedMat(fin,nodes,nrNodes,adjMatrix,nrArcs);

    fprintf(fout,"bfs traversal: ");
    bfs_traversal(nrNodes,adjMatrix,nodes);
    fprintf(fout,"\n");

    fprintf(fout,"dfs traversal: ");
    dfs_traversal(nrNodes,adjMatrix,nodes);


    fclose(fin);
    fclose(fout);
    return 0;
}

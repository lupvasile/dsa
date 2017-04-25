///first node in date.in is the start, second node is the destination

#include <stdio.h>
#include <string.h>
#include "IO_Management.h"
#include "list.h"

FILE *fin,*fout;

#define inf 0x3f3f3f3f

int findMin(int dist[],int used[],int n)
{
    int minn = inf;
    int res = n;
    for(int i = 0; i < n; ++i)
        if(minn > dist[i] && !used[i])
        {
            minn = dist[i];
            res = i;
        }

    return res;
}

void dijkstra(int start,int nrNodes, ListT *adj[], int dist[],int dad[], int ldadl[])
{
    int used[nrNodes];
    memset(used,0,sizeof used);
    dist[start] = 0;
    dad[start] = -1;
    ldadl[start] = -1;
    while(1)
    {
        int node = findMin(dist,used,nrNodes);
        if(node == nrNodes) break;

        used[node] = 1;
        if(adj[node] == NULL) continue;

        NodeT *ptr = adj[node]->first;
        EdgeT *vec;
        for(; ptr; ptr = ptr->next)
        {
            vec = ptr->pData;

            if(dist[node] + vec->val < dist[vec->node])
            {
                dist[vec->node] = dist[node] + vec->val;
                dad[vec->node] = node;
                ldadl[vec->node] = vec->val;
            }
        }
    }

}

void printPath(int node,int dad[])
{
    if(dad[node]!=-1)
    {
        int ok = 0;
        if(dad[dad[node]] == -1) ok = 1;
        printPath(dad[node],dad);
        if(ok) dad[node] = -1;
        fprintf(fout,"-%d",node);
    }
    else fprintf(fout,"%d",node);
}
void printLen(int node,int dad[],int ldadl[])
{
    if(dad[node]!=-1)
    {
        printLen(dad[node],dad,ldadl);
        fprintf(fout,",%d",ldadl[node]);
    }
    else fprintf(fout,"%d",ldadl[node]);
}

int main(int argc,char* argv[])
{
    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    int nrArcs,start,finish;
    fscanf(fin,"%d %d\n",&start,&finish);

    int nrNodes = getNrNodes(fin,&nrArcs);
    fscanf(fin,"%d %d\n",&start,&finish);
    int nodes[nrNodes],dad[nrNodes],dist[nrNodes],ldadl[nrNodes];

    EdgeT arcs[nrArcs];

    ListT *adjList[nrNodes];
    memset(adjList,0,sizeof adjList);

    readArcs(fin,nodes,nrNodes,adjList,arcs);

    memset(dist,inf,sizeof dist);
    memset(dad,-1,sizeof dad);
    dijkstra(start,nrNodes,adjList,dist,dad,ldadl);

    if(dist[finish] == inf)
    {fprintf(fout,"no route");
    return 0;
    }

    fprintf(fout,"%d ",dist[finish]);

    printPath(finish,dad);
    fprintf(fout," (");
    printLen(finish,dad,ldadl);
    fprintf(fout,")");

    fclose(fin);
    fclose(fout);
    return 0;
}

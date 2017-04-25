#include <stdio.h>
#include <string.h>
#include "TEST.h"
#include "IO_Management.h"
#include "list.h"


int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


int main(int argc,char* argv[])
{
    FILE *fin,*fout;
    fin = openCheck(argv[1],"w");
    makeTest(fin);///currently nr_nodes and nr_arcs is 1e5
    fclose(fin);

    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    int nrNodes = getNrNodes(fin);
    int nodes[nrNodes];
    int bufLen = getMaxLen(fin," \n");
    char graphName[bufLen];

    readNodes(fin,graphName,nodes,nrNodes);
    qsort(nodes,nrNodes,sizeof(nodes[0]),cmp);

    ListT *adjList[nrNodes];
    memset(adjList,0,sizeof adjList);

    int nrArcs = getNrArcs(fin);
    readArcsNormalised(fin,nodes,nrNodes,adjList,nrArcs);

    int nrSub = getNrNodes(fin);
    int nodesSub[nrSub];
    readNodes(fin,graphName,nodesSub,nrSub);

    int used[nrNodes];
    memset(used,0,sizeof(used));

    for(int i = 0; i < nrSub; ++i)
        used[binSrc(nodes,nrNodes-1,nodesSub[i])] = 1;

    fprintf(fout,"%s arcs",graphName);
    for(int i = 0; i < nrNodes; ++i)
        if(used[i] && adjList[i])
    {
        NodeT *ptr = adjList[i]->first;
        for(;ptr;ptr = ptr->next)
            if(used[ptr->key])
                fprintf(fout," (%d %d)",nodes[i],nodes[ptr->key]);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

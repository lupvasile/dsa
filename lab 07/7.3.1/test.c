#include "TEST.h"

void makeTest(FILE *fout)
{
    srand(time(NULL));

    int from = nr_nodes;
    int to = nr_nodes * 2 - 1;
    int i;

    fprintf(fout,"GraphMare nodes");
    for(i = from;i<=to;++i)
        fprintf(fout," %d",i);
    fprintf(fout,"\n");

    fprintf(fout,"GraphMare arcs");
    for(i = 1; i <= nr_arcs; ++i)
    {
        int x = 1ll*rand()*rand() % nr_nodes;
        int y = 1ll*rand()*rand() % nr_nodes;
        fprintf(fout," (%d %d)",x+from,y+from);
    }

    fprintf(fout,"\n");
    fprintf(fout,"Subgraph nodes");
    int sub = rand()%nr_nodes;

    for(i = 0;i<sub;++i)
    {
        int x = 1ll*rand()*rand() % nr_nodes;
        fprintf(fout," %d",x+from);
    }

}

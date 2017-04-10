#include "TEST.h"

void makeTest(FILE *fout)
{
    int i = 0;

    for(i = 1;i<=nr_entry;++i)
        fprintf(fout,"i%d\n",i);

    fprintf(fout,"l\n");

    for(i = 1;i<=nr_entry + 2;++i)
        fprintf(fout,"f%d\n",i);

    for(i = 1;i<=nr_entry + 2;++i)
        fprintf(fout,"d%d\n",i);

    fprintf(fout,"l\n");

    //for(i = 1;i<=nr_entry + 2;++i)
      //  fprintf(fout,"fName number %d\n",i);

}

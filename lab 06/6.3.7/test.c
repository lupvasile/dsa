#include "TEST.h"

void makeTest(FILE *fout)
{
    int i = 0;

    for(i = 1;i<=nr_entry;++i)
        fprintf(fout,"iString number %d\n",i);

    fprintf(fout,"l\n");

    for(i = 1;i<=nr_entry + 2;++i)
        fprintf(fout,"fString number %d\n",i);

    for(i = 1;i<=nr_entry + 2;++i)
        fprintf(fout,"dString number %d\n",i);

    fprintf(fout,"l\n");


}

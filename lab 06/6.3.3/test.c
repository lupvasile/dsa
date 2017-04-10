#include "TEST.h"

void makeTest(FILE *fout)
{
    int i = 0;

    for(i = 1;i<=nr_entry;++i)
        fprintf(fout,"i978-1-%05d-072-8\n",i);

    fprintf(fout,"l\n");

    for(i = 1;i<=nr_entry + 2;++i)
        fprintf(fout,"f978-1-%5d-072-8\n",i);

    for(i = 1;i<=nr_entry + 2;++i)
        fprintf(fout,"d978-1-%5d-072-8\n",i);

    fprintf(fout,"l\n");

    //for(i = 1;i<=nr_entry + 2;++i)
      //  fprintf(fout,"fName number %d\n",i);

}

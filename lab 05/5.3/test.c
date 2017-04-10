#include "TEST.h"

void makeTest(FILE *fout)
{
    int i = 0;

    for(i = 1;i<=nr_MED;++i)
        fprintf(fout,"iMedicine number %d,7.65,6,20150702,20190702\n",i);

    for(i = 1;i<=nr_MED;++i)
        fprintf(fout,"uMedicine number %d,~,~,~,~,~\n",i);

    fprintf(fout,"ce");

    for(i = 1;i<=nr_MED;++i)
        fprintf(fout,"dMedicine number %d\n",i);

    for(i = 1;i<=nr_MED;++i)
        fprintf(fout,"iMedicine number %d,7.65,6,20150702,20160702\n",i);

    for(i = 1;i<=nr_MED;++i)
        fprintf(fout,"uMedicine number %d,Updated Medicine number %d,4,4,20140705,20160702\n",i,i);

    fprintf(fout,"ce");
}

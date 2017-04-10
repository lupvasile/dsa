#include "pharma.h"

ItemT *createItem()
{
    ItemT *p = malloc(sizeof(ItemT));
    if(p == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

    p->amount = p->price = p->dateOfExpiration = p->dateOfManufacturing = -inf;
    return p;
}

char readOp(FILE *fin)
{
    char c;
    while(c = fgetc(fin))
    {
        if(c == EOF) return c;
        if(strchr("idcu",c)!=NULL) break;
    }

    return c;
}

int expirat(void *it)
{
    time_t rawtime;
    time(&rawtime);
    return difftime(((ItemT*)it)->dateOfExpiration, rawtime) < 0;
}

ItemT *getItem(FILE *fin)
{
    ItemT *p = createItem();

    fscanf(fin,"%[^,]200s",p->name);
    fgetc(fin);

    fscanf(fin,"%lf",&(p->price));
    fgetc(fin);
    if(p->price == -inf) fgetc(fin);

    fscanf(fin,"%lf",&(p->amount));
    fgetc(fin);
    if(p->amount == -inf) fgetc(fin);

    int year = -inf,month = -inf,day = -inf;
    fscanf(fin,"%4d%2d%2d",&year,&month,&day);
    fgetc(fin);

    struct tm time;
    time.tm_sec = time.tm_hour = time.tm_min = 0;

    if(year == -inf) fgetc(fin);
    else
    {


        time.tm_year = year - 1900;
        time.tm_mon = month - 1;
        time.tm_mday = day;

        p->dateOfManufacturing = mktime(&time);
    }

    fscanf(fin,"%4d%2d%2d",&year,&month,&day);
    if(year == -inf) return p;
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day;

    p->dateOfExpiration = mktime(&time);

    return p;
}


#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "insolve.h"

#define DEBUG 0

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

void solve_case(int id,  enum MODES mode, ListT *ptrRoad, ListT *ptrGarage, FILE *fout)
{

    switch (mode)
    {
    case ON_ROAD:
            insertAtRear(ptrRoad,createNode(id));
        break;
    case SHOW_ROAD:
        fprintf(fout,"road: ");
        printList(fout,ptrRoad);
        fprintf(fout,"\n");
        break;
    case SHOW_GARAGE:
        fprintf(fout,"garage: ");
        printList(fout,ptrGarage);
        fprintf(fout,"\n");
        break;
    case ENTER_GARAGE:
    {
        if(!isEmpty(ptrRoad))
            if(ptrRoad->first->key == id)
            {
                NodeT *ptr = deleteFirst(ptrRoad);
                insertAtRear(ptrGarage,ptr);
            }
            else fprintf(fout,"error %d not at garage entrance!\n",id);
        else fprintf(fout,"error %d not at garage entrance!\n",id);
        break;
    }

    case EXIT_GARAGE:
        if(!isEmpty(ptrGarage))
            if(ptrGarage->first->key == id)
            {
                NodeT *ptr = deleteFirst(ptrGarage);
                insertAtRear(ptrRoad,ptr);
            }
            else fprintf(fout,"error %d not at exit!\n",id);
        else fprintf(fout,"error %d not at exit!\n",id);

        break;

    };
}


int main(int argc,char *argv[])
{

#if DEBUG
    FILE *fin = openCheck("date.in","r");
    FILE *fout = openCheck("date.out","w");
    fout = stdout;
#else
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");
#endif

    ListT *ptrRoad;
    ListT *ptrGarage;

    ptrRoad = createList();
    ptrGarage = createList();

    char buf[1024];

    while(fgets(buf,sizeof buf,fin))
    {
        int id;
        enum MODES mode;
        getData(buf,&id,&mode);
        solve_case(id,mode,ptrRoad,ptrGarage,fout);
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

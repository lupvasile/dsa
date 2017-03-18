#include "insolve.h"

///receives a buffer as input
///gets id and mode from buffer and puts them in respective pointers
void getData(char *buf,int *ptrId, enum MODES *ptrMode)
{
    char *sModes[] = {"On_road","Enter_garage","Exit_garage","Show_trucks(road)","Show_trucks(garage)"};
    int i;
    for(i = 0; i < nrMODES; i++)
        if(strstr(buf,sModes[i]))
    {
        *ptrMode = i;
        break;
    }

    if(i == nrMODES)
    {
        printf("not permitted operaton %s\n",buf);
        return;
    }

    if(i == SHOW_ROAD || i == SHOW_GARAGE) return;

    char *p = strchr(buf,'(');
    sscanf(p+1,"%d",ptrId);
}

#ifndef INSOLVE_H_INCLUDED
#define INSOLVE_H_INCLUDED

#include <string.h>
#include <stdio.h>

#define nrMODES 5
enum MODES {ON_ROAD,ENTER_GARAGE, EXIT_GARAGE, SHOW_ROAD, SHOW_GARAGE};

void getData(char *buf,int *ptrId,  enum MODES *ptrMode);
#endif // INSOLVE_H_INCLUDED

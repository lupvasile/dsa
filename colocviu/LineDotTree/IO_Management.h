#ifndef IO_MANAGEMENT_H_INCLUDED
#define IO_MANAGEMENT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *openCheck(const char *name,const char *mode);
int getMaxLen(FILE *f, char *delim);///returns max length of a string without characters from delim

#endif // IO_MANAGEMENT_H_INCLUDED

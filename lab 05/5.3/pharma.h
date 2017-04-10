#ifndef PHARMA_H_INCLUDED
#define PHARMA_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 202
#define inf 0x3f3f3f3f

typedef struct ph_item
{
    char name[NAME_SIZE];
    double price;
    double amount;
    time_t dateOfManufacturing;
    time_t dateOfExpiration;
} ItemT;

char readOp(FILE *fin);
ItemT *getItem(FILE *fin);
int expirat(void *it);

#endif // PHARMA_H_INCLUDED

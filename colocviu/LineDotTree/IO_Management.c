#include "IO_Management.h"

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

int getMaxLen(FILE *f, char *delim)
{
    int maxLen = 0, currLen = 0;

    while(1)
    {
        char ch;
        ch = getc(f);
        if(ch == EOF || strchr(delim,ch) != NULL)
        {
            if(currLen > maxLen) maxLen = currLen;
            currLen = 0;

            if(ch == EOF) break;
            continue;
        }

        currLen++;
    }

    rewind(f);
    return maxLen;
}

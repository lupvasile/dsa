#include <stdio.h>
#include <stdlib.h>
#include "LDTree.h"

int main()
{
    FILE *dict = openCheck("LineDot-code.txt","r");
    FILE *fin = openCheck("translated.txt","r");
    FILE *fout = openCheck("plain.txt","w");

    LD_NodeT *root = LineDotCodeTree(dict);

    int bufLen = getMaxLen(fin," \n")+2;
    char buf[bufLen];

    char ch,lch = NOCHAR;///lch: last char to know when to print a space

    do
    {
        long pos = ftell(fin);
        lch = ch;
        ch = fgetc(fin);
        if(ch == EOF) break;
        if(ch == ' ')
        {
            if(lch == ' ') fprintf(fout,"%c",ch);
            continue;
        }

        fseek(fin,pos,SEEK_SET);///go previous 1 character
        if(fscanf(fin,"%s",buf) == EOF) break;

        ch = translate(root,buf);
        if(ch != NOCHAR) fprintf(fout,"%c",ch);
        lch = NOCHAR;

    }while(1);

    fclose(fin);
    fclose(fout);
    fclose(dict);

    return 0;
}

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");
#define cout fout

#define PI 3.14159265359

int main()
{
    for(int i = 0;i<5;++i){
    double U, ZL, UB, I, RC, P, cosp, XL,RL,URC, UC,L,w,UL,XC,C;
    fin>>I>>URC>>UB>>UC>>P;
    U = 50;
    //RL = P/(I*I);
    RL = 3.8;
    ZL = UB / I;
    RC = URC / I;
    XL = sqrt(ZL*ZL - RL*RL);
    cosp = P/(U*I);
    w = 2*PI*50;
    L = XL / w;
    UL = sqrt(UB*UB - (RL*I)*(RL*I));
    XC = UC/I;
    C = 1e6 / (w*XC);
    //cout<<"   XL      POWER    I  cosp\n";
    cout<<fixed<<setprecision(3)<<setw(9)<<XL<<' '<<I<<"\n\n";//<<' '<<I<<' '<<cosp<<"\n\n";

    //cout<<C<<'\n';
    }
    return 0;
}

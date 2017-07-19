#include "rsa.h"

vector<ZZ> RSA::extendido_euclides(ZZ a, ZZ b)
{
    
    ZZ r1, r2, x1, x2, y1, y2;
    r1=a, r2=b, x1=1,x2=0, y1=0, y2=1;
    if (b>a){
        r1=b;
        r2=a;
    }
    ZZ q,r,x,y;
    while (r2>0){
        q=r1/r2;
        r=r1-q*r2;
        r1=r2;
        r2=r;
        x=x1-q*x2;
        x1=x2;
        x2=x;
        y=y1-q*y2;
        y1=y2;
        y2=y;
    }
    vector<ZZ> v;
    v.push_back(x1); // x1 coef del mayor
    v.push_back(y1); // y1 coef del menor
    v.push_back(r1);
    
    return v;
}


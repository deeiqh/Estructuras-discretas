#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ mod(ZZ a, ZZ b){
    ZZ q;
    q=a/b;
    ZZ x;
    x = a-(q*b);
    return x;
}

ZZ exponenciacion(ZZ num, ZZ exp, ZZ mod_){
    ZZ res;
    res=1;
    if(exp%2==1){
        res=mod(num,mod_);
        num=res;
        exp=exp/2;
    }
    while(exp>=1){
        num=mod(num*num,mod_);
        if (exp%2==1){
            res=mod(res*num,mod_);
        }
        exp=exp/2;
    }
    return res;
}
int main()
{
    ZZ a, b, c;
    a = 2656341623; 
    b = 432;
    c = 234;
    cout<<exponenciacion(a,b,c)<<endl;
    return 0;
}

/*
void euclides_extendido(ZZ a, ZZ b){

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

    cout<<x1<<endl;
    cout<<y1<<endl;
}
*/

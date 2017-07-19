#include "rsa.h"    

ZZ RSA::modulo(ZZ a,ZZ b){
    ZZ q,r;
    if(a<0){
        a *= -1;
        q=a/b;
        r=a-(q*b);
        r*= -1;
        r += b;
    }
    else{ 
        q=a/b;
        r=a-(q*b);        
    }

    return r;    
}

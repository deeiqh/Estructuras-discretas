#include "rsa.h"

 ZZ RSA::inversa(ZZ a, ZZ m)
 {
    ZZ e;
    if(a < m)
        e = extendido_euclides(a, m)[1];
    else
        e = extendido_euclides(a, m)[0];
    if (e < 0)
        return modulo(e,m);
    else
        return e;
 }

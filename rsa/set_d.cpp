#include "rsa.h"

void RSA::set_d()
{
    // d = e^-1 (mod phi)
    
    ZZ phi;
    phi = (p-1)*(q-1);
    /*
    if(test_primalidad(phi) && (modulo(e,phi) != 0)){ // fermat
        d = exponenciacion(e,phi-2,phi);
        cerr << "fermat, set d";
    }
    else*/
        d = inversa(e,phi);
    cerr << "done set_d";
}


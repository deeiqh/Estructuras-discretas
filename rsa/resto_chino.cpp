#include "rsa.h"

ZZ RSA::resto_chino(vector<ZZ> const &n, vector<ZZ> const &p)
{
    long l = n.size();
    
    ZZ pp; // P
    pp = 1;
    for(int i = 0; i != l; i++)
       pp *= p[i];
    
    vector<ZZ> ppi; // Pi
    vector<ZZ> qi; // qi
    ZZ resultado;
    resultado = 0;
    for(int i = 0; i != l; i++){
        ppi.push_back(pp/p[i]);
        qi.push_back(inversa(ppi[i],p[i]));  
        resultado += modulo(n[i]*ppi[i]*qi[i], pp);
    }
    
    return modulo(resultado,pp); 
}

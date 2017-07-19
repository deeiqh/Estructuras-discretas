#ifndef RSA_H
#define RSA_H

#include <NTL/ZZ.h>
#include <string>
#include <vector>

using namespace NTL;
using namespace std;

class RSA
{
private:
    int bits;
    string alfabeto;    
    ZZ p;    
    ZZ q;    
    ZZ N;    
    ZZ e;
    ZZ d;
public:
    RSA(int bits_){
        bits = bits_;
        alfabeto = 
       "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    };
    RSA(ZZ,ZZ){};
    
    void set_p(){p = generar_aleatorio(bits/2 +1);}   
    void set_q(){q = generar_aleatorio(bits/2 -1);} 
    void set_N(){N = p*q;} 
    void set_e();///
    void set_d();///
    ZZ get_e(){return e;}
    ZZ get_N(){return N;}

    //virtual ~RSAC(void){};
    ZZ modulo(ZZ a,ZZ b);///
    ZZ exponenciacion(ZZ , ZZ, ZZ);///
    
    ZZ generar_aleatorio(int bits);///    
    ZZ generar_aleatorio(ZZ a, ZZ b);///
    bool test_primalidad(ZZ);///
    
    ZZ euclides(ZZ a, ZZ b);///
    vector<ZZ> extendido_euclides(ZZ a, ZZ b);/// v[0] = x1 (del mayor); v[1] = y1(del menor)
    ZZ inversa(ZZ a, ZZ m);/// m es el módulo
    
    ZZ resto_chino(vector<ZZ> const &n, vector<ZZ> const &p);/// n = numeros, p = primos entre si
    
    string cifrar(RSA &receptor, string const &mensaje);///
    string descifra_mensaje(string const &mensaje);//
    
};

#endif

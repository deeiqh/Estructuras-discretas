#include <iostream>
#include <string>
#include <NTL/ZZ.h>
#include <vector>

using namespace std;
using namespace ntl;

ZZ lehmer_gcd(ZZ x, ZZ y);
ZZ euclides_extendido(ZZ a, ZZ b);
ZZ exponenciacion(ZZ num, ZZ exp, ZZ mod);

class Cripto
{
private:
    const unsigned int num_bits = 1024;
    ZZ p, q, n, phi;
    GenPrime(p, num_bits, 80); //80 es el margen de error, 2^-80
    GenPrime(q, num_bits, 80);
    n = p*q;
    phi = (p-1)(q-1);
    ZZ e;
    gen_e(e,phi);
    ZZ d;
    gen_d(d,e,phi);
    
public:
    Cripto(){};
    
    ZZ get_e(){return e;}
    ZZ get_d(){return d;}
    ZZ get_n(){return n;}
    
    vector<ZZ> cifrar_rsa(ZZ e, ZZ n, vector<ZZ> msje)
    {
        vector<ZZ> resultado;
        for(auto &x:msje){
            //por el Teorema de Euler, se podría simplificar la operación
            if ((e-1)%phi == 0)
                resultado += x;
            else                          
                resultado += exponenciacion(x, e, n);
        }
        return resultado;
    }
    
    vector<ZZ> descifrar_rsa(ZZ d, ZZ n, vector<ZZ> msje)
    {        
        vector<ZZ> resultado;
        for(auto &x:msje){
            //por el Teorema de Euler, se podría simplificar la operación
            if ((d-1)%phi == 0)
                resultado += x;
            else                          
                resultado += exponenciacion(x, d, n);
        }
        return resultado;
    }
    
};

void Cripto::gen_e(ZZ& e, const ZZ& phi)
{
    for(e = phi-1; e != 1;e -= 1){
        if(lehmer_gcd(e, phi) == 1)
            break;
    }
}

void Cripto::gen_d(ZZ& d,const ZZ& e, const ZZ& phi)
{
    d = euclides_extendido(e, phi) % phi;
}

int main() {
    
    vector<ZZ> t_p{12, 13, 14, 15};
    
    Cripto emisor;    
    Cripto receptor;
    
    vector<ZZ> v, v2;    
    cout << "texto cifrado." << '\n';
    for(auto &x: t_p)
        v += emisor.cifrar_rsa(emisor.get_e(), emisor.get_n(), x) << '\n';
    
    cout << "texto descifrado." << '\n';
    for(auto &x: v)
        v2 += emisor.cifrar_rsa(emisor.get_e(), emisor.get_n(), x) << '\n';
    
    return 0;
}

ZZ lehmer_gcd(ZZ x, ZZ y)
{
    ZZ x_, y_, a, b, c, d;
    ZZ q, q_, t, tt, u;
    ZZ grupos_x;
    ZZ grupos_y;
    ZZ base;
    base = 1000; // determina un arreglo de potencias de la base.
    ZZ *arr_potencias = genera_array_base(base); // se crea un array con las potencias de la base.
                                       // si es base 2 se trata de una forma especial (moviendo bits)
    while(y >= base){
        x_ = digitos_base(x, arr_potencias, grupos_x ); // x_ tendrá los dígitos más significativos que unidos serán <= a la base.
                              // la función usa búsqueda binaria en el array de potencias  de la base
        y_ = digitos_base(y, arr_potencias, grupos_y);

        a = 1; b = 0; c = 0; d = 1;
        if(grupos_x == grupos_y){ //necesario pues en la siguiente vuelta hay que asegurar que x e y tengan la misma cantidad d cifras
            while( ((y_+c) != 0) && ((y_+d) != 0) ){
                q = (x_+a) / (y_+c);
                q_ = (x_+b)/ (y_+d);
                if (q != q_){
                    break;
                }
                t=a-q*c;
                a = c;
                c = t;
                t = b - q*d;
                b = d;
                d = t;
                t = x_ - q*y_;
                x_ = y_;
                y_ = t;
            }
        }
        if (b == 0){
            tt = x%y;
            x = y;
            y = tt;
        }
        else{
            tt = a*x + b*y;
            u = c*x + d*y;
            x = tt;
            y = u;
        }
    }
    
    ZZ v;
    v = dijkstra_euclides(x,y);
    
    return v;
}

ZZ euclides_extendido(ZZ a, ZZ b){
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
    return x1;
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


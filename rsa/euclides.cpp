#include "rsa.h"
#include <limits.h>

ZZ lehmer_gcd(ZZ x, ZZ y);

ZZ RSA::euclides(ZZ a, ZZ b)
{
    return lehmer_gcd(a, b);
}

#define MAX_POTENCIAS 3 

ZZ lehmer_gcd(ZZ x, ZZ y);
ZZ dijkstra_euclides( ZZ a,  ZZ b);

ZZ *genera_array_base(ZZ base);
ZZ digitos_base(ZZ num, ZZ arr[], int &grupos);

ZZ lehmer_gcd(ZZ x, ZZ y)
{
    ZZ x_, y_, a, b, c, d;
    ZZ q, q_, t, tt, u;
    int grupos_x;
    int grupos_y;
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

ZZ *genera_array_base(ZZ base)
{
    //repetir el primer y último elemento para
    //  retornar lo deseado en la busq. binaria
    //  así se agregan dos elementos más
    ZZ *arr = new ZZ[MAX_POTENCIAS+2];
    arr[0] = base;
    ZZ potencia;
	potencia = 1;
    for(int i = 1; i != MAX_POTENCIAS+1; i++){
        potencia *= base;
        arr[i] = potencia;
    }
    arr[MAX_POTENCIAS+1] = potencia;

    return arr;
}

int b_binaria(ZZ num, ZZ arr[], int low, int high); // devuelve el valor de la
                                                    // potencia <= num dentro de arr
ZZ digitos_base(ZZ num, ZZ arr[], int &grupos)
{
    grupos = b_binaria(num, arr, 0, MAX_POTENCIAS+2 -1);
    if (grupos == 0)
        grupos = 1;
    else
        if (grupos == MAX_POTENCIAS+1 )
            grupos = MAX_POTENCIAS;
    return num / arr[grupos];
}

int b_binaria(ZZ x, ZZ arr[], int low, int high)
{
    int medio;
    if (high > low)
        medio= (high-low)/2 + low;
    else
        medio = (low-high)/2 + low;
    if(arr[medio] == x || (low > high))
        return (low-1); //medio == low, asi retorna la potencia menor de la base
    else{
        if (arr[medio] < x)
            return b_binaria(x,arr,medio+1, high);
        else
            return b_binaria(x,arr,low,medio-1);
    }
}

ZZ dijkstra_euclides( ZZ a,  ZZ b){
    if(a==0 || b==0)
        return (a+b);
    else if(a>b){
        a%=b;
        return dijkstra_euclides(a,b);
    }
    else if(b>a){
        b%=a;
        return dijkstra_euclides(a,b);
    }
}

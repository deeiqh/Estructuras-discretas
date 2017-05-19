/*
INPUT
    Dos números x, y (x>=y) enteros positivos en cierta base b.
OUTPUT
    mcd(x,y).
*/

#include <iostream>
#include <limits.h>

#define MAX_POTENCIAS 3 // para generar un arreglo de potencias de la base

using namespace std;
using Tipo = unsigned int;

void lehmer_gcd(Tipo x, Tipo y);
Tipo dijkstra_euclides( Tipo a,  Tipo b);

int main()
{
    double segs;

    Tipo x = 768454923;//x = 768454923;
    Tipo y = 542167814;//y = 542167814;

    cout << "Aplicando Lehmer, gcd(" << x << ',' << y << ")\n";
    lehmer_gcd(x,y);

    int dj;
    clock_t t_ini = clock();
    dj = dijkstra_euclides(x,y);
    clock_t t_fin = clock();
    cout << dj << " en " << (double)(t_fin - t_ini)*1000.0 / CLOCKS_PER_SEC;
    return 0;
}

Tipo *genera_array_base(Tipo base);
Tipo digitos_base(Tipo num, Tipo arr[], Tipo &grupos);

void lehmer_gcd(Tipo x, Tipo y)
{
    clock_t t_ini = clock();

    Tipo x_, y_, a, b, c, d;
    Tipo q, q_, t, tt, u;
    Tipo grupos_x;
    Tipo grupos_y;
    Tipo base = 1000; // determina un arreglo de potencias de la base.
    Tipo length_bits = sizeof(int)*CHAR_BIT;
    Tipo *arr_potencias = genera_array_base(base); // se crea un array con las potencias de la base.
                                       // si es base 2 se trata de una forma especial (moviendo bits)
    while(y >= base){

        x_ = digitos_base(x, arr_potencias, grupos_x ); // x_ tendrá los dígitos más significativos que unidos serán <= a la base.
                              // la función usa búsqueda binaria en el array de potencias  de la base
        y_ = digitos_base(y, arr_potencias, grupos_y);
	/*
        x_ = x >> (length_bits -MAX_POTENCIAS +1); //mejor mover en base 2. si se hace en base 10 se pirde mucha significancia
        y_ = y >> (length_bits- MAX_POTENCIAS +1); // beta^p = beta³ = 10³ = base = 1000 = 2^10 -> se mueven 10 bits.
                                                    // Pero si se usa 10 se demora t, con (length_bits - MAX_POTENCIAS +1) le
                                                    // toma menos, t/2, es un número "adecuado".
	*/
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

    clock_t t_fin = clock();

    cout << "Lehmer redujo a gcd(" << x << ',' << y << ") en ";
    double segs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    cout << segs * 1000.0 << " milisegundos. \n" << '\n';

    cout << "Aplicando euclides(dijkstra): gcd(" << x << ',' << y << ") = ";

    t_ini = clock();
    Tipo v = dijkstra_euclides(x,y);
    t_fin = clock();

    cout << v << '\n';

    segs += (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    cout << "\nTiempo total:" << segs * 1000.0 << " milisegundos" << '\n';


}

Tipo *genera_array_base(Tipo base)
{
    //repetir el primer y último elemento para
    //  retornar lo deseado en la busq. binaria
    //  así se agregan dos elementos más
    Tipo *arr = new Tipo[MAX_POTENCIAS+2];

    arr[0] = base;
    Tipo potencia = 1;
    for(Tipo i = 1; i != MAX_POTENCIAS+1; i++){
        potencia *= base;
        arr[i] = potencia;
    }
    arr[MAX_POTENCIAS+1] = potencia;

    return arr;
}

Tipo b_binaria(Tipo num, Tipo arr[], Tipo low, Tipo high); // devuelve el valor de la
                                                    // potencia <= num dentro de arr
Tipo digitos_base(Tipo num, Tipo arr[], Tipo &grupos)
{
    grupos = b_binaria(num, arr, 0, MAX_POTENCIAS+2 -1);
    if (grupos == 0)
        grupos = 1;
    else
        if (grupos == MAX_POTENCIAS+1 )
            grupos = MAX_POTENCIAS;
    return num / arr [grupos];
}

Tipo b_binaria(Tipo x, Tipo arr[], Tipo low, Tipo high)
{
    Tipo medio;
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

Tipo dijkstra_euclides( Tipo a,  Tipo b){
    if(a==0 || b==0)
        return a+b;
    else if(a>b){
        a%=b;
        return dijkstra_euclides(a,b);
    }
    else if(b>a){
        b%=a;
        return dijkstra_euclides(a,b);
    }
}

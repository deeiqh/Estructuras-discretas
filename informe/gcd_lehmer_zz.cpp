/*
INPUT
    Dos números x, y (x>=y) enteros positivos en cierta base b.
OUTPUT
    mcd(x,y).
*/

#include <iostream>
#include <limits.h>
#include<NTL/ZZ.h>

#define MAX_POTENCIAS 3 // para generar un arreglo de potencias de la base

using namespace std;
using namespace NTL;
typedef ZZ Tipo;

void lehmer_gcd(Tipo x, Tipo y);
Tipo dijkstra_euclides( Tipo a,  Tipo b);

int iteraciones = 0;
int main()
{
    double segs;

	Tipo x, y;
	SetBit(x,16);
    	SetBit(y,16);    

	x = 34245;
	y = 8655;

    cout << "Aplicando Lehmer, gcd(" << x << ',' << y << ")\n";
    lehmer_gcd(x,y);

    Tipo dj;
    clock_t t_ini = clock();
    dj = dijkstra_euclides(x,y);
    clock_t t_fin = clock();
    cout << dj << " en " << (double)(t_fin - t_ini)*1000.0 / CLOCKS_PER_SEC << '\n';

    cout << "Iteraciones totales: " << iteraciones << '\n';
    return 0;
}

Tipo *genera_array_base(Tipo base);
Tipo digitos_base(Tipo num, Tipo arr[], int &grupos);

void lehmer_gcd(Tipo x, Tipo y)
{
    clock_t t_ini = clock();

    Tipo x_, y_, a, b, c, d;
    Tipo q, q_, t, tt, u;
    int grupos_x;
    int grupos_y;
    Tipo base;
	base = 1000; // determina un arreglo de potencias de la base.
    Tipo length_bits;
	length_bits = sizeof(int)*CHAR_BIT;
    Tipo *arr_potencias = genera_array_base(base); // se crea un array con las potencias de la base.
                                       // si es base 2 se trata de una forma especial (moviendo bits)

    cout << x <<"&"<< y << "\n";
    while(y >= base){
        iteraciones++;
        x_ = digitos_base(x, arr_potencias, grupos_x ); // x_ tendrá los dígitos más significativos que unidos serán <= a la base.
                              // la función usa búsqueda binaria en el array de potencias  de la base
        y_ = digitos_base(y, arr_potencias, grupos_y);
        cout << grupos_x <<"&"<< grupos_y <<"\n";
	/*
        x_ = x >> (length_bits -MAX_POTENCIAS +1); //mejor mover en base 2. si se hace en base 10 se pirde mucha significancia
        y_ = y >> (length_bits- MAX_POTENCIAS +1); // beta^p = beta³ = 10³ = base = 1000 = 2^10 -> se mueven 10 bits.
                                                    // Pero si se usa 10 se demora t, con (length_bits - MAX_POTENCIAS +1) le
                                                    // toma menos, t/2, es un número "adecuado".
	*/
        cout << x_ <<"&"<< y_ << "\n";
        a = 1; b = 0; c = 0; d = 1;
        cout << a <<"&"<< b <<"&"<< c <<"&"<< d <<"\n";
        if(grupos_x == grupos_y){ //necesario pues en la siguiente vuelta hay que asegurar que x e y tengan la misma cantidad d cifras
            while( ((y_+c) != 0) && ((y_+d) != 0) ){
                iteraciones++;
                q = (x_+a) / (y_+c);
                q_ = (x_+b)/ (y_+d);
                cout << q <<"&"<< q_ <<"\n";
                if (q != q_){
                    break;
                }
                t=a-q*c;
                a = c;
                cout << a <<"\n";
                c = t;
                cout << c <<"\n";
                t = b - q*d;
                b = d;
                cout << b <<"\n";
                d = t;
                cout << d <<"\n";
                t = x_ - q*y_;
                x_ = y_;
                cout << x_ <<"\n";
                y_ = t;
                cout << y_ <<"\n";
            }
        }
        if (b == 0){
            tt = x%y;
            x = y;
            cout << x <<"\n";
            y = tt;
            cout << y <<"\n";
        }
        else{
            tt = a*x + b*y;
            u = c*x + d*y;
            x = tt;
            cout << x <<"\n";
            y = u;
            cout << y <<"\n";
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
    Tipo potencia;
	potencia = 1;
    for(int i = 1; i != MAX_POTENCIAS+1; i++){
        potencia *= base;
        arr[i] = potencia;
    }
    arr[MAX_POTENCIAS+1] = potencia;

    return arr;
}

int b_binaria(Tipo num, Tipo arr[], int low, int high); // devuelve el valor de la
                                                    // potencia <= num dentro de arr
Tipo digitos_base(Tipo num, Tipo arr[], int &grupos)
{
    grupos = b_binaria(num, arr, 0, MAX_POTENCIAS+2 -1);
    if (grupos == 0)
        grupos = 1;
    else
        if (grupos == MAX_POTENCIAS+1 )
            grupos = MAX_POTENCIAS;
    return num / arr[grupos];
}

int b_binaria(Tipo x, Tipo arr[], int low, int high)
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

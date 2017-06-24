#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;

#define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
#define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

void criba(int n) {

      clock_t t_ini = clock();

      int nr = static_cast<int>(sqrt(static_cast<double> (n))); // raiz cuadrada de n

      int* NoPrimos = new int[n+1];// ultimo elemento es n

      //seteo el bit array, asumimos que son primos
      memset(NoPrimos, 0, sizeof(int) * (n + 1));


      for (int m = 2; m <= nr; m++) {
            if (!TestBit(NoPrimos, m)){//if (!isComposite[m]) {
                  cout << m << '\n';
                  for (int k = m * m; k <= n; k += m)//mejora de arrancar con el cuadrado del primo
                        SetBit(NoPrimos,k);
            }
      }

      clock_t t_fin = clock();
      
      //cout << "\n\n";
      double segs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
      //cout << segs * 1000.0 << " milisegundos. \n" << '\n';
      
      //cout << "\n\n";
      for (int m = nr; m <= n; m++)
            if(!TestBit(NoPrimos,m))
                  cout << m << '\n';
                  
      delete [] NoPrimos;
}


int main()
{
   criba(1000000000);
}


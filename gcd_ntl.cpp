#include <NTL/ZZ.h>
#include <ctime>

using namespace std;
using namespace NTL;

ZZ euclides(ZZ, ZZ);

int main()
{
   ZZ num1, num2;

   cin >> num1;
   cin >> num2;

   ZZ menor, mayor;
    if(num1 < num2){
        menor = num1;
        mayor = num2;
    }
    else{
        menor = num2;
        mayor = num1;
    }

   time_t t_ini, t_fin;
   t_ini = clock();

   cout << euclides(mayor, menor) << "\n";

   t_fin = clock();
   cout << static_cast<double>(t_fin - t_ini);

}

ZZ euclides(ZZ mayor, ZZ menor)
{
    if (menor == 0) return mayor;
    else
        return euclides(menor, mayor%menor);
}

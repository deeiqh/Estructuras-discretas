#include "rsa.h"

long miller_rabin(RSA *obj,const ZZ& n, const ZZ& x)
{
   ZZ m, y, z;
   long j, k;

   if (x == 0) return 0;

   //n-1 = 2^k * m

   k = 1;
   m = n/2;
   while (m % 2 == 0) {
      k++;
      m /= 2;
   }

   z = obj->exponenciacion(x, m, n); 
   if (z == 1) return 0;

   j = 0;
   do {
      y = z;
      z = (y*y) % n; 
      j++;
   } while (j < k && z != 1);

   return z != 1 || y != n-1;
}

bool RSA::test_primalidad(ZZ n)
{
    //miller-rabin
    
    if (n <= 1) return 0;

    ZZ x;
    int i;
    int t = 40;
    for (i = 0; i < t; i++) {
      x = RandomBnd(n);
      if (miller_rabin(this, n, x))
         return 0;
    }

    return 1;
}
/*
    ZZ numero, mod;
    numero = emisor.generar_aleatorio(1024);
    
    do{
        mod = emisor.modulo(numero,conv<ZZ>(2));
        if (mod == 0)
            numero += 1;
        else 
            numero += 2;
    }while(emisor.test_primalidad(numero));
    
    cout << numero << " yes\n";
*/

#include<iostream>
#include<fstream>
#include<NTL/ZZ.h>

#define n_bits 1024
#define n_bytes n_bits/8

using namespace std;
using namespace NTL;

ZZ module(ZZ x,ZZ y){
    ZZ q=x/y,r;
    if(q<0)
    {
        q=-1*q;
        q++;
        q=-1*q;
        r=x-(q*y);
    }
    else 
    {
        r=x-(q*y);
    }
    return r;
}

ZZ power(ZZ x,ZZ y, ZZ p)
{
    ZZ res = conv<ZZ>(1);      // Initialize result
    x = module(x,p);  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        
        ZZ oper;
        ZZ one;
        one =1;
        NTL::bit_and(oper,y,one);
        //cout << oper ;
        if(conv<int>(oper))
            res = module((res*x) , p);

        // y must be even now
        y = y>>1; // y = y/2
        x = module((x*x) , p);
    }
    return res;
}

bool miillerTest(ZZ d, ZZ n)
{
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    ZZ a = module((conv<ZZ>(2 + rand())) , (n - 4));

    // Compute a^d % n
    ZZ x = power(a, d, n);
    if (x == 1  || x == n-1)
       return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n-1)
    {
        x = module((x * x) , n);
        d *= 2;

        if (x == 1)      return false;
        if (x == n-1)    return true;
    }

    // Return composite
    return false;
}

bool isPrime(ZZ n, ZZ k)
{
    // Corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    ZZ d = n - 1;
    while (module(d , conv<ZZ>(2)) == 0)
        d /= 2;

    // Iterate given nber of 'k' times
    for (ZZ i =conv<ZZ>(0); i < k; i++)
         if (miillerTest(d, n) == false)
              return false;

    return true;
}

int main()
{
    //GENERAR RANDOMS DE 1024 BITS
    
    //leer 128 bytes de /dev/random
    fstream dev;
    dev.open("/dev/urandom", fstream::binary | fstream::in);
    if(dev){
        char arr[n_bytes]; // 128 bytes = 1024 bits         
        dev.read(arr, n_bytes);
        dev.close();
        /*       
        unsigned int e = arr[127];
        cout << e << '\n';  
        */
        
        //(void ZZFromBytes(ZZ& x, const unsigned char *p, long n)   
        ZZ numero;     
        unsigned char arr2[n_bytes];
        for(int i = 0; i != n_bytes; i++)
            arr2[i] = arr[i];        
        ZZFromBytes(numero, arr2, n_bytes);
        
             
        
        //MILLER
        ZZ k = conv<ZZ>(4);
        ZZ mod;
        mod = module(numero,conv<ZZ>(2));
        if(mod != 0){
                while(!isPrime(numero, k)){
                     numero += 2;   
                     mod = module(numero,conv<ZZ>(2));
                     if (mod == 0)
                        numero += 1;
                        
                }
                cout << numero << '\n'; 
                cout << "yes\n";
        }
      
    }   
    else
        cerr<< "No abierto";
        
    

    
    
    return 0;
}






















#include<iostream>
#include<fstream>
#include<NTL/ZZ.h>

#define n_bits 1024
#define n_bytes n_bits/8

using namespace std;
using namespace NTL;

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
        
        cout << numero << '\n';        
    }   
    else
        cerr<< "No abierto";
        
    //MILLER
    
    //http://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
    
    
    return 0;
}

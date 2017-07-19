#include "rsa.h"
#include <list>

ZZ RSA::generar_aleatorio(int bits)
{  
    long n_bytes;
    (bits%8 == 0)?n_bytes = bits/8 : n_bytes = bits/8 +1;    
      
    unsigned char arr[n_bytes];
    list<unsigned char> l;
    memcpy(arr, &l, n_bytes);
    
    ZZ numero;
    ZZFromBytes(numero, arr, n_bytes);
    long correr = n_bytes*8 - bits;
    numero >>= correr;
    
    return numero;
}

ZZ RSA::generar_aleatorio(ZZ a, ZZ b)
{

    long li = NumBits(a);
    long ls = NumBits(b);
    
    long cant_bits_diferencia = ls - li; 
    ZZ num1;
    ZZ num2;
    do{
    num1 = generar_aleatorio(cant_bits_diferencia-1);
    num2 = generar_aleatorio(cant_bits_diferencia-2);
    }while(num1 == 0 or num2 == 0);
    
    ZZ num3;
    NTL::bit_xor(num3, num1, num2);
    if (a == 0)
        return num3;
    return num3*a;
    
    
    /*
    long n_bytes;    
    (NumBits(ld)%8==0)?n_bytes = NumBits(ld)/8 : n_bytes = NumBits(ld)/8 +1;
    cout << n_bytes<<'\n';
    unsigned char arr[n_bytes];
    memcpy(arr, &a, n_bytes);
    unsigned char arr2[n_bytes];
    memcpy(arr2, &b, n_bytes);
    
    for(int i = 0; i != n_bytes; i++)
        arr2[i] ^= arr[i];
        
    ZZ numero;
    ZZFromBytes(numero, arr2, n_bytes);
    cout << "numerooo " << numero << '\n';
    cout << "long numerooo " << NumBits(numero) << '\n';
    long correr = n_bytes*8 - NumBits(ld);
    cout << "n_bytes: " << n_bytes << "\n\n\n";
    cout << "correr " << correr << '\n';
    numero >>= correr;
    cout << "numerooo " << numero << '\n';
    numero += li;   
    cout << "numerooo " << numero << '\n';
    //leo "numero" de bits
    (conv<long> (numero)%8==0)?n_bytes = conv<long> (numero)/8 : n_bytes = conv<long> (numero)/8 +1;
    unsigned char arr3[n_bytes];
    char c;
    memcpy(arr3, &c, n_bytes);
    ZZ numero2;
    ZZFromBytes(numero2, arr3, n_bytes);
    
    correr = n_bytes*8 - conv<long> (numero);
    numero2 >>= correr;
    
    return numero2;
    */
}

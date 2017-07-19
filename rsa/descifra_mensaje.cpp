#include "rsa.h"
#include <sstream>

string RSA::descifra_mensaje(string const &mensaje)
{
    stringstream is;    
    is << N;
    string n(is.str());
   
    unsigned int N_digitos = n.length();
    
    //bloques de N_digitos    
    int pos = 0;
    string secuencia(mensaje);
    int secuencia_long = secuencia.length();
    
    string s_bloque;
    string resultado("");
    while(pos <= secuencia_long){        
        s_bloque = secuencia.substr(pos,N_digitos);
        pos += N_digitos;
        
        //operar el s_bloque como zz, construye un resultado con bloques de tamaño k+1
        
        
        string arr;
        int i=0; int j =0;
        while(i != s_bloque.length()){
            if(s_bloque[i] == '0' && j==0 );
            else{
                arr += s_bloque[i];
                j++;
            }
            i++;
        }
    
        ZZ c,num;  
        num = 0; 
        for(int i=0; i !=arr.length();i++){
            num += pow(10,i)*arr[arr.length()-1-i];
        }
 
        c = exponenciacion(num, d, N);
        string c_bloque("");       
        
        stringstream is;
        is << c;    
        string sc(is.str());

        for (int i = 0; i!= N_digitos-1-sc.length(); i++){  
            c_bloque += '0';
        }
        c_bloque += sc;
        
        resultado += c_bloque;      
    }
    
    string resultado2("");
    string s_letra;// de "17" es, de "2" es 3
    int aa;
    for (int i = 0; i!= resultado.length();){  
        if(resultado[i] == '0'){
            aa = resultado[i] - '0';
            resultado2 += alfabeto[aa];
        }
        else{            
            aa = 10*(resultado[i]-'0');
            aa += resultado[i+1] - '0';
            resultado2 += alfabeto[aa];
        }
        i += 2;
    }
    return resultado2;
}










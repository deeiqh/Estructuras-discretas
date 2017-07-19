#include "rsa.h"
#include <sstream>

string RSA::cifrar(RSA &receptor, string const &mensaje)
{
    //formato a numeros de mensaje   
    
    string s_letra;// de r es "17", de c es "2"
    
    string secuencia("");
    for (int i = 0; i!= mensaje.length(); i++){        
        s_letra = to_string(alfabeto.find(mensaje[i]));
        if(s_letra.length() == 1)
            secuencia += "0"+s_letra;
        else
            secuencia += s_letra;
    }

    //dividir el mensaje en bloques
    
    stringstream is;    
    is << receptor.get_N();        
    string n(is.str());
   
    unsigned int N_digitos = n.length();
    unsigned int k = N_digitos-1;
        //cantidad de bloques compatible
    ZZ l, kz;
    
    l = conv<ZZ>(secuencia.length());
    
    kz = conv<ZZ>(k);
        
    while(modulo(l,kz)!= 0){    
        secuencia += to_string(26);
        l += 2;
    }
    
        //bloques de k    
    int pos = 0;
    int secuencia_long = secuencia.length();
    string s_bloque;
    string resultado("");
    while(pos <= secuencia_long){        
        s_bloque = secuencia.substr(pos,k);
        pos += k;
        
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
            num += pow(10,i)*(arr[arr.length()-1-i]-'0');
        }
 
        c = exponenciacion(num, receptor.get_e(), receptor.get_N());
        string c_bloque("");       
        
        stringstream is;
        is << c;    
        string sc(is.str());

        for (int i = 0; i!= N_digitos-sc.length(); i++){  
            c_bloque += '0';
        }
        c_bloque += sc;
        
        resultado += c_bloque;      
    }
    return resultado;
}

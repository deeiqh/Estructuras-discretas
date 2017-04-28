#include <iostream>
#include <string>

using namespace std;

class Cripto
{
public:
    string alfabeto = "abcdefghijklmnopqrstuvwxyz*";
    int clave = 53;
    
    Cripto(){};
    
    string cifrar_caesar(string msje_tp)
    {
        string resultado = "";
        for(char &letra:msje_tp){
            resultado += alfabeto[(alfabeto.find(letra)+clave)%27];
        }
        return resultado;
    }
    
    string descifrar_caesar(string msje_cifrado)
    {
        string resultado = "";
        for(char &letra:msje_cifrado){
            int i = alfabeto.find(letra) - (clave % 27);
            if (i < 0  )
                resultado += alfabeto[( i+27)];
            else
                resultado += alfabeto[( i )];
                
        }
        return resultado;
    }
    
};

int main() {
    
    string t_p = "****kjihgfedcbazyxwvutsrqponmlabcdefghijkl**mnopqrstuvwxyz*";
    cout << "texto plano: " << t_p << '\n';
    
    Cripto emisor;    
    Cripto receptor;
    
    cout << "texto cifr: " << emisor.cifrar_caesar(t_p) << '\n';
    cout << "texto descifr: " << receptor.descifrar_caesar( emisor.cifrar_caesar(t_p));
    
    return 0;
}


#include <iostream>
#include <string>

using namespace std;

class Cripto
{
public:
    string alfabeto = "abcdefghijklmnopqrstuvwxyz*";
    int a = 25;
    int b = 7;

    Cripto(){};

    string cifrar_afin(string st)
    {
        string resultado = "";
        int m = alfabeto.size();
        for(auto &letra:st){
           int t = alfabeto.find(letra);
           resultado += alfabeto[(a*t+b)%m];
        }
        return resultado;
    }

    string descifrar_afin(string sc)
    {
        string resultado = "";
        int m = alfabeto.size();
        int s = euclides_extendido(a,m);
        for(auto &letra:sc){
            int t = alfabeto.find(letra);
            resultado += alfabeto[(s*(t-b))%m];

        }
        return resultado;
    }

    int euclides_extendido(int a,int b){
        int r1=a,r2=b,s1=1,s2=0,t1=0,t2=1;
        while (r2>0) {
            int q=r1/r2;

            int r=r1-q*r2;
            int s=s1-q*s2;
            int t=t1-q*t2;

            r1=r2;
            r2=r;
            s1=s2;
            s2=s;
            t1=t2;
            t2=t;
        }
        return s1;
    }


};

int main() {

    string t_p = "hola*mundo";
    cout << "texto plano: " << t_p << '\n';

    Cripto emisor;
    Cripto receptor;

    cout << "texto cifr: " << emisor.cifrar_afin(t_p) << '\n';
    cout << "texto descifr: " << receptor.descifrar_afin( emisor.cifrar_afin(t_p));

    return 0;
}

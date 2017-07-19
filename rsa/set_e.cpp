#include "rsa.h" 
void RSA::set_e()
{
    ZZ phi, mod, eucli;
    ZZ dos, uno;
    dos = 2; uno = 1;
    phi = (p-1)*(q-1);   
    
    e = generar_aleatorio(dos,phi);
   
    do{
        mod = modulo(e,dos);        
        if (mod == 0)
             e += 1;
        else 
             e += 2;     
        cout << e << phi << "\n\n\n";
        eucli = euclides(e,phi);
    }while(eucli != uno);
    cerr << "done set_e" << '\n';
}

#include "rsa.h"

ZZ RSA::exponenciacion(ZZ num, ZZ exp, ZZ mod_){
/*
    if(test_primalidad(mod_))//fermat 1 
        if(modulo(num,mod_) != 0 && (exp == mod_-1))
            return conv<ZZ>(1);
        if(exp == mod_)//fermat 2
            return num;
  */          
    ZZ res;
    res=1;
    if(exp%2==1){
        res=modulo(num,mod_);
        num=res;
        exp=exp/2;
    }
    while(exp>=1){
        num=modulo(num*num,mod_);
        if (exp%2==1){
            res=modulo(res*num,mod_);
        }
        exp=exp/2;
    }
    return res;
}

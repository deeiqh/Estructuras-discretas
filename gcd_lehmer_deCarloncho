#include<iostream>
#include<time.h>

using namespace std;

long length(int n){
  int d=1;
  if(n<=9){
    return d;
  }
  else{
    return d+length(n/10);
  }
}
long radix(long b,long zx,long *a,long *t){
  long i=0;
  long za=zx;
  long xa[length(zx)];
  long zq=za/b;
  a[i]=za-zq*b;
  while(zq>0l){
    i++;
    za=zq;
    zq=za/b;
    a[i]=za-zq*b;
  }
  *t=i;
  zx=a[*t];
  return zx;
}
void lehmer(long x,long y,long b){
  long u,t,T;
  long xp,yp,q,Q,A,B,C,D;
  long xt,yt,xa[length(x)],ya[length(y)];
  while(y>=b){
    xp=radix(b,x,xa,&xt);
    yp=radix(b,y,ya,&yt);
    cout<<*ya<<"\t"<<yt<<"\t"<<yp<<endl;
    cout<<*xa<<"\t"<<yt<<"\t"<<xp<<endl;
    A=1;D=1;B=0;C=0;
    if(xt==yt){
      while((yp+C)!=0 && (yp+D)!=0){
        q=(xp+A)/(yp+C);
        Q=(xp+B)/(yp+D);
        cout<<xp<<"\t"<<yp<<"\t"<<A<<"\t"<<B<<"\t"<<C<<"\t"<<D<<"\t"<<q<<"\t"<<Q<<endl;
        if(q!=Q) break;
        t=A-q*C;A=C;C=t;
        t=B-q*D;B=D;D=t;
        t=xp-q*yp;xp=yp;yp=t;
      }
    }
    if(B==0l){
      T=x%y;x=y;y=T;
    }
    else{
      T=A*x+B*y;
      u=C*x+D*y;
      x=T;
      y=u;
    }
    cout<<x<<"\t"<<y<<endl;
  }
  while(y>0){
    u=x%y;
    x=y;
    y=u;
    cout<<x<<"\t"<<y<<endl;
  }
  cout<<"fin de lehmer"<<endl;
  cout<<x<<endl;
}
int main(int argc, char const *argv[]) {
  long x,y,b;
  while(true){
    clock_t init=clock();
    cin>>x>>y>>b;
    lehmer(x,y,b);
    clock_t fin=clock_t();
    cout<<"redujo a"<<endl;
    double seg=(double)(fin-init)/CLOCKS_PER_SEC;
    cout<<seg*1000.0<<"milisegundos\n";
  }
    return 0;
}

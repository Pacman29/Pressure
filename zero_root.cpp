#include "zero_root.h"
#include <math.h>
#include <QDebug>

double Zero_root_Dichotomy(double a, double b, double (*f)(double, double), double n, int flag)
{
//    double c=(a+b)/2;
//    if (flag == 0)
//    {
//        qDebug()<< "f: ";
//        qDebug()<<(f(n,b));
//        qDebug()<<(f(n,a));
//        qDebug()<< "-------";
//    }

//    while(fabs(f(n,b)-f(n,a))>(double)(0.0001))
//    {
//        if (flag == 0)
//            qDebug()<<(f(n,b)-f(n,a));
//        (f(n,a)*f(n,c)<0)?(b=c):(a=c);
//        c=(a+b)/2;
//    }
//    return c;


    double root;
    double f1,f2,froot;
    double root1;
    double fb;
    double eps = 1e-6;
    root=(a+b)/2.0;
    do
    {
      f1 = f(n,a);
      f2 = f(n,b);
      froot = f(n,root);
//      if(f1*f2<=0)
//        b=root;
//      else
//        a=root;
      if(f1*froot<0)
          b = root;
      else //if (froot*f2<0)
          a = root;
      root1 = root;
      root = (a+b)/2.0;
      fb = fabs((b-a))/root;
      //fb = fabs(b-a);
    }while(fb > eps);
//    for(double i = 14.9; i<=15.1; i+=0.001)
//        qDebug() << f(n,i) << i;
    return root;
}




#include "legandre_poli.h"
#include <math.h>
double Legandre_Poly(const double n, double x)
{
    switch ((int)n) {
    case 0:     return 1;
    case 1:     return x;
    default:    return (double)((2*n-1)*x*Legandre_Poly(n-1, x) - (n-1)*Legandre_Poly(n-2, x))/(double)n;
    }
}

double *Legandre_Roots(const int n)
{
    double del = (double)2/n;
    double* x = new double[n];
    for(double i=-1; i<=1; i+=del)
        *(x++) = dichotomy(i,i+del, Legandre_Poly,n);
    return x-n-1;
}

double dichotomy(double a, double b, double (*f)(double, double), double n)
{
    double root;
    root=(a+b)/2;
    while((fabs(b-a)>1e-6)&&f(n,root)!=0)
    {
      if(f(n,a)*f(n,root)<0)
        b=root;
      else
        a=root;
      root=(a+b)/2;
    }
    return root;
}

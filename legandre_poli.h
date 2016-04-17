#ifndef LEGANDRE_POLI_H
#define LEGANDRE_POLI_H
#include "zero_root.h"

double Legandre_Poly(const double n, double x);
double* Legandre_Roots(const int n);
double dichotomy(double a, double b, double (*f)(double, double), double n);

#endif // LEGANDRE_POLI_H

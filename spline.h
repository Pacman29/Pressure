#ifndef SPLINE_H
#define SPLINE_H
typedef struct spline_
{
double a,b,c,d,x;
}spline;
spline *Spline_Calc_spline(double* x_arr, double *y_arr, int n);
double spline_calculate(spline *splines, double x, int n);
double Spline_Multivariate(double *x_arr, double *y_arr, double **M, int n, int m, double x, double y);


#endif // SPLINE_H

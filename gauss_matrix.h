#ifndef GAUSS_MATRIX_H
#define GAUSS_MATRIX_H

int Gauss_matrix_Gauss(double **mass, int n, double **x);
double** Gauss_matrix_Init(int n);
void  Gauss_matrix_del_mt(double **M, int n);


#endif // GAUSS_MATRIX_H

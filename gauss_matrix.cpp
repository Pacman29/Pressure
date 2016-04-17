#include "gauss_matrix.h"
#include <QDebug>

int Gauss_matrix_Gauss(double **mass, int n, double **x)
{
    int i,j,k;
    *x=new double [n];//выделение памяти для неизвестных
    //прямой ход
    for( i = 0; i < n; i++)
    {
        double a=mass[i][i];
        for( j = i+1; j < n; j++)
        {
            double b=mass[j][i];
            for( k = i; k < n+1; k++)
                mass[j][k]=mass[i][k]*b-mass[j][k]*a;
        }
    }
//обратный ход
    for( i = n-1; i >= 0; i--)
    {
        double summ=0.;
        for( j = i+1; j < n; j++)
            summ+=mass[i][j]*(*x)[j];
        summ=mass[i][n]-summ;
        if(mass[i][i]==0)
            return 0;
        (*x)[i]=summ/mass[i][i];
        qDebug()<<(*x)[i]<<i;
    }
    return 1;
}

double **Gauss_matrix_Init(int n)
{
    double **x = new double*[n];
    if (x == 0)
        return 0;
    for(int i = 0; i < n; ++i)
    {
        x[i] = new double[n+1];
        if (x[i] == 0)
        {
            Gauss_matrix_del_mt(x,n);
            return 0;
        }
    }
    return x;
}

void Gauss_matrix_del_mt(double **M, int n)
{
    for(int i = 0; i < n; ++i)
        delete [] M[i];
    delete [] M;
}


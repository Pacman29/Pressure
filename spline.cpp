#include "spline.h"
#include "math.h"
#include <QDebug>
#define h(i) (x_arr[i] - x_arr[i-1])
//double Spline_Calc_spline(double *x_arr, double *y_arr,int n, double x)
//{
//    double A,B,D,F,z;
//    double ksi[--n+2], etta[n+2];
//    double *c = new double[n+2];
//    ksi[2]=0;
//    etta[2]=0;
//    int i;
//    for(i=2;i<=n;i++)
//    {
//        A = h(i-1);
//        D = h(i);
//        B = -2*(A + D);
//        F = -3*((y_arr[i]-y_arr[i-1])/D - (y_arr[i-1]-y_arr[i-2])/A);
//        z = B - A*ksi[i];
//        ksi[i+1] = D/z;
//        etta[i+1] = (F+A*etta[i])/z;
//    }
//    c[n+1] = 0;
//    c[1] = 0;
//    for(i=n;i>1;i--)
//        c[i] = ksi[i+1]*c[i+1] + etta[i+1];
//    int pos = 0;
//    if (x<=x_arr[0])
//        pos = 0;
//    if (x>=x_arr[n-1])
//        pos = n-1;
//    for(int i=0;i<n-1;i++)
//        if((x>=x_arr[i])&&(x<x_arr[i+1]))
//            pos = i+1;
//    pos = -1;

//    if(!pos)
//        pos++;


//    double a = y_arr[pos-1];
//    double b = (y_arr[pos] - y_arr[pos-1])/h(pos) - h(pos)*(double)(c[pos+1]+2*c[pos])/3;
//    double d = (c[pos+1]-c[pos])/(3*h(pos));
//    double y = a + b*(x-x_arr[pos-1]) + c[pos]*pow(x-x_arr[pos-1],2) + d*pow(x-x_arr[pos-1],3);
//    delete c;
//    return y;
//}
spline* Spline_Calc_spline(double *x_arr, double *y_arr,int n)
//spline* make_spline(const point *points, int n)
{
    spline *splines = new spline[n];
    for (int i = 0; i < n; i++)
    {
        splines[i].x = x_arr[i];
        splines[i].a = y_arr[i];
    }
    splines[0].c = 0;

    // Решение СЛАУ относительно коэффициентов сплайнов c[i] методом прогонки для трехдиагональных матриц
    // Вычисление прогоночных коэффициентов - прямой ход метода прогонки

    double *alpha = new double[n-1];
    double *beta = new double[n-1];
    double A, B, C, F, h_i, h_i1, z;
    alpha[0] = beta[0] = 0;
    for (int i = 1; i < n - 1; i++)
    {
        h_i =  x_arr[i] -  x_arr[i-1], h_i1 =  x_arr[i+1] -  x_arr[i];
        A = h_i;
        C = 2 * (h_i + h_i1);
        B = h_i1;
        F = 6 * ((y_arr[i+1] -  y_arr[i]) / h_i1 - (y_arr[i] -  y_arr[i-1]) / h_i);
        z = (A * alpha[i - 1] + C);
        alpha[i] = -B / z;
        beta[i] = (F - A * beta[i - 1]) / z;
    }

    splines[n - 1].c = (F - A * beta[n - 2]) / (C + A * alpha[n - 2]);

    // Нахождение решения - обратный ход метода прогонки
    for (int i = n - 2; i > 0; --i)
        splines[i].c = alpha[i] * splines[i + 1].c + beta[i];

    // Освобождение памяти, занимаемой прогоночными коэффициентами
    delete beta;
    delete alpha;

    // По известным коэффициентам c[i] находим значения b[i] и d[i]
    for (int i = n - 1; i > 0; --i)
    {
        double h_i = x_arr[i] -  x_arr[i-1];
        splines[i].d = (splines[i].c - splines[i - 1].c) / h_i;
        splines[i].b = h_i * (2 * splines[i].c + splines[i - 1].c) / 6 + (y_arr[i] -  y_arr[i-1]) / h_i;
    }

    return splines;
}


//  Вычисление значения функции
double spline_calculate(spline *splines, double x, int n)
{
    spline *s;
    if (x <= splines[0].x) // Если x меньше точки сетки x[0] - пользуемся первым эл-том массива
        s = splines + 1;
    else if (x >= splines[n - 1].x) // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
        s = splines + n - 1;
    else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
    {
        int i = 0, j = n - 1;
        while (i + 1 < j)
        {
             int k = i + (j - i) / 2;
             if (x <= splines[k].x)
                j = k;
             else
                i = k;
            }
            s = splines + j;
        }

        double dx = (x - s->x);
        return s->a + (s->b + (s->c / 2 + s->d * dx / 6) * dx) * dx; // Вычисляем значение сплайна в заданной точке.
}


double Spline_Multivariate(double *x_arr, double *y_arr, double **M, int n, int m, double x, double y) // x = p , y = temp
{
    double tmp[n];
    for(int i = 0; i<n; ++i)
    {
        spline *s = Spline_Calc_spline(x_arr,M[i],m);
        tmp[i] = spline_calculate(s,x,m);
//        qDebug()<<i<<tmp[i];
        delete[] s;
    }

    spline *s = Spline_Calc_spline(y_arr,tmp,n);
    double res = spline_calculate(s,y,n);
//    qDebug()<<"res"<<res<<"X:"<<x<<"Y:"<<y;
    delete []s;
    return res;
}



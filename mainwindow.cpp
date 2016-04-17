#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "legandre_poli.h"
#include "gauss_matrix.h"
#include "spline.h"
#include <math.h>
#include <QDebug>
#define VALUE 0.00263
//#define VALUE 6.179180887372013651877133105802

int m,n,m_in;

double Tw,T0;

double *p,*t;
double **tab;
double _integr(double a, double b, int n,double (*f)(double, double), double p);
double _function(double n, double pressure);
double _fun(double z, double p_p);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Result_lbl->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QString dir = QFileDialog::getOpenFileName(this,tr("Загрузить файл"),QDir::currentPath(),tr("Таблица (*.txt)"));
    if (dir == "")
    {
        error::ERROR(this,NO_TABLE);
        return;
    }
    ui->statusBar->showMessage("Таблица: "+dir);
    _read_table_from_file(ui->tableWidget,dir);

}

void MainWindow::on_pushButton_clicked()
{
    m = ui->tableWidget->columnCount()-1;
    n = ui->tableWidget->rowCount();
    p = new double[m];
    t = new double[n];
    tab = new double*[n];
    for (int i = 0; i<n; ++i)
        tab[i] = new double[m];
    bool ok;
    for (int i = 0; i<m;++i)
        p[i] = ui->tableWidget->horizontalHeaderItem(i+1)->text().toDouble(&ok);

    for (int i = 0; i<n;++i)
        t[i] = ui->tableWidget->item(i,0)->text().toDouble(&ok);

    for(int i = 0; i<n;++i)
        for(int j = 0; j<m; ++j)
            tab[i][j] = ui->tableWidget->item(i,j+1)->text().toDouble(&ok);

    T0 = ui->T0_box->value();
    Tw = ui->Tw_box->value();
    int count = ui->N_box->value();
    m_in = ui->m_box->value();

    double p1 = 5.2;
    double p2 = 25;

    double res = Zero_root_Dichotomy(p1,p2,_function,count,0);

    QMessageBox::information(this,tr("Результат"),QString::number(res));
    delete p;
    delete t;
    Gauss_matrix_del_mt(tab,n);
}

void MainWindow::_read_table_from_file(QTableWidget *tb, QString dir)
{
    QFile f(dir);
    if(!f.open(QIODevice::ReadOnly))
    {
        error::ERROR(this,NO_FILE);
        return;
    }
    QTextStream stream(&f);
    QStringList list;
    list = stream.readLine().split(QRegExp("[ \t]"),QString::SkipEmptyParts);
    for(int i = 0; i< list.size();++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(list[i]);

        tb->setHorizontalHeaderItem(i,item);
    }
    while(!stream.atEnd())
    {
        list = stream.readLine().split(QRegExp("[ \t]"),QString::SkipEmptyParts);
        tb->setRowCount(tb->rowCount()+1);
        for(int i = 0; i< list.size();++i)
        {
            QTableWidgetItem *item = new QTableWidgetItem(list[i]);
            tb->setItem(tb->rowCount()-1,i,item);
        }
    }
}

double _integr(double a, double b, int n,double (*f)(double, double), double p)
{
    double *mas = Legandre_Roots(n);
//    for(int i = 0; i<n; i++)
//        qDebug()<<i<<mas[i];
    double **M = Gauss_matrix_Init(n);
    //заполняем матрицу коэф ti в нужных степенях
    int i,j;
    for( i=0; i<n ;i++)
        for(j=0; j<n ;j++)
        M[i][j] = pow(mas[j],i);
    //создаем столбец решений
    for(i=0;i<n;i++)
        M[i][n] = (double)2/(i+1) * ((i+1)%2);
    double *r;
    Gauss_matrix_Gauss(M,n,&r);

    double sum=0,x;
    //вычисляем интеграл
    for(i=0;i<n;i++)
    {
        x = (double)((b-a)*mas[i]+b+a)/2;
        double t = ((Tw-T0)*pow(x,m_in)+T0);
        double fun = f(t,p);
        sum += r[i]*fun*x;
        //qDebug()<<i<<r[i];
    }
    sum*=(b-a)/2;
    delete r;
    delete mas;
    Gauss_matrix_del_mt(M,n);

    return sum;
}

double _function(double n, double pressure)
{
    return _integr(0,1,n,_fun,pressure)-VALUE/2;
}

double _fun(double z, double p_p)
{
    return Spline_Multivariate(p,t,tab,n,m,p_p,z);
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QTableWidget>
#include <QTextStream>
#include <QTableWidgetItem>
#include <error.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;
    void _read_table_from_file(QTableWidget *tb,QString dir);
};

#endif // MAINWINDOW_H

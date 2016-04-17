#ifndef ERROR_H
#define ERROR_H
#include <QMessageBox>

enum error_type{NO_ERR,NO_TABLE,NO_FILE};

class error
{
public:

    static int ERROR(QWidget *parent,error_type err);

signals:

public slots:
};

#endif // ERROR_H

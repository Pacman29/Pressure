#include "error.h"
int error::ERROR(QWidget *parent,error_type err)
{
    QString err_msg;
    switch (err) {
    case NO_TABLE:
        err_msg = "Таблица не загружена";
        break;
    case NO_FILE:
        err_msg = "Невозможно открыть файл";
        break;
    case NO_ERR:
        return NO_ERR;
    }
    QMessageBox::warning(parent,"Ошибка",err_msg);
    return err;
}

#ifndef GETDATA_H
#define GETDATA_H

#include <QDialog>
#include <QSqlTableModel>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Getdata;
}
QT_END_NAMESPACE


class Getdata : public QDialog
{
    Q_OBJECT

public:
    explicit Getdata(QWidget *parent = nullptr);
    ~Getdata();

private:
    Ui::Getdata *ui;
    QSqlTableModel *model;
    DBManager * dbmanager;
    int row;
};

#endif // GETDATA_H

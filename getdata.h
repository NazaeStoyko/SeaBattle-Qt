#ifndef GETDATA_H
#define GETDATA_H

#include <QDialog>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE

namespace Ui {
QT_END_NAMESPACE
class Getdata;
}


class QSqlTableModel;
class DBManager;
class Getdata : public QDialog
{
    Q_OBJECT

public:
    explicit Getdata(QWidget *parent = nullptr);
    ~Getdata();

private slots:
  //  void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Getdata *ui;
    QSqlQuery *query;
    QSqlTableModel *model;
    DBManager * dbmanager;
    int row;


};

#endif // GETDATA_H

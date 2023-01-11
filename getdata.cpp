#include "getdata.h"
#include "ui_getdata.h"
#include "sqlitedbmanager.h"


Getdata::Getdata(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Getdata)
{
    ui->setupUi(this);
    dbmanager = SqliteDBManager::getInstance();
    dbmanager->connectToDataBase();

    model = new QSqlTableModel(this, dbmanager->getDB());
    model->setTable("players");
    model->select();
    ui->tableView->setModel(model);
}

Getdata::~Getdata()
{
    delete ui;
}

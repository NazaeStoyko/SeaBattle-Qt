#include "choose.h"
#include "ui_choose.h"

Choose::Choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
}


Choose::~Choose()
{
    delete ui;
}


void Choose::on_information_clicked()
{
    getdata = new Getdata;
    getdata->show();
}


void Choose::on_exit_clicked()
{
    QApplication::quit();
}


void Choose::on_restart_clicked()
{
    emit accepted();
}


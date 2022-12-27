#include "form.h"
#include "ui_form.h"
#include "dbmanager.h"
#include "player.h"
#include "sqlitedbmanager.h"

Form::Form( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    dbmanager = SqliteDBManager::getInstance();


    ui->setupUi(this);

}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    Player newPlayer(ui->lineEdit->text(), ui->lineEdit_2->text().toInt());
    dbmanager->inserIntoTable(newPlayer);
    hide();
}





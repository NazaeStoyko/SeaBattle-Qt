#include "form.h"
#include "ui_form.h"
#include "player.h"
#include "sqlitedbmanager.h"
#include "mainwindow.h"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    dbmanager = SqliteDBManager::getInstance();
    ui->setupUi(this);
    ui->pbEnter->hide();
    connect(ui->Age, &QLineEdit::textChanged, this, &Form::onFieldsAreFilled);
    connect(ui->Nick, &QLineEdit::textChanged, this, &Form::onFieldsAreFilled);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pbEnter_clicked()
{
    Player newPlayer(ui->Age->text(), ui->Nick->text().toInt());
    dbmanager->inserIntoTable(newPlayer);
    this->hide();
    DifficultyLevel difficultyLevel = ui->rbHard->isChecked() ? DifficultyLevel::HARD : DifficultyLevel::NORMAL;
    MainWindow* w = new MainWindow(difficultyLevel);
    w->show();
}

void Form::onFieldsAreFilled()
{
    if(!ui->Age->text().isEmpty() && !ui->Nick->text().isEmpty())
    {
        ui->pbEnter->show();
    } else
    {
        ui->pbEnter->hide();
    }
}

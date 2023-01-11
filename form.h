#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();
    //void on_Form_accepted();

private:
    Ui::Form *ui;
    DBManager *dbmanager;

};

#endif // FORM_H

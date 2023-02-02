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
    void on_pbEnter_clicked();
    void onFieldsAreFilled();

private:
    Ui::Form *ui;
    DBManager *dbmanager;

};

#endif // FORM_H

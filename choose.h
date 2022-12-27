#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>
#include "getdata.h"


namespace Ui {
class Choose;
}

class Choose : public QDialog
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = nullptr);
    ~Choose();

private slots:
    void on_information_clicked();
    void on_exit_clicked();
    void on_restart_clicked();

private:
    Ui::Choose *ui;
    Getdata *getdata;
};

#endif // CHOOSE_H

#ifndef MAIN
#define MAIN

#include "mainwindow.h"
#include "form.h"
#include <QApplication>

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    Form form;
    form.setModal(true);
    form.exec();

    return a.exec();
}

#endif

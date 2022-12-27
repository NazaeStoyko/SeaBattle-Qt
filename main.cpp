#include "mainwindow.h"
#include "form.h"
#include <QApplication>

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    MainWindow w;
    w.show();

    Form form;
    form.setModal(true);
    form.exec();

    return a.exec();
}









































//Робочий код



//#include "mainwindow.h"

//#include <QApplication>


//int main( int argc, char* argv[] )
//{
//    QApplication a( argc, argv );

//    MainWindow w;
//    w.show();
//    return a.exec();
//}


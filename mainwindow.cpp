#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QRandomGenerator>
#include "field.h"

const int N = 10;

//void MainWindow::startGame()
//{
////    myFieldImage->createBoard();
////    myFieldImage->redraw();
////    enemyFieldImage->createBoard();
////    enemyFieldImage->redraw();


//    qDebug()<<"startGame";
//}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pictures = new Images();
    pictures->load();

    myFieldImage = new Field(pictures,40,39,216,217);
    enemyFieldImage = new Field(pictures,322,39,214,217);
    enemyFieldImage->isEnemy = true;
   // chooseDialog = new Choose(this);


    board->drawShips();

    myFieldImage->redraw();
    enemyFieldImage->redraw();




//    connect(chooseDialog, &Choose::accepted, this, &MainWindow::startGame);
//    connect(chooseDialog, &Choose::accepted, chooseDialog, &Choose::hide);

  // startGame();
}

MainWindow::~MainWindow()
{
    delete pictures;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,this->menuBar()->geometry().height(),pictures->get("field"));
    painter.drawImage(myFieldImage->getX(),this->menuBar()->geometry().height()+myFieldImage->getY(),myFieldImage->getImage());
    painter.drawImage(enemyFieldImage->getX(),this->menuBar()->geometry().height()+enemyFieldImage->getY(),enemyFieldImage->getImage());
}

void MainWindow::mousePressEvent( QMouseEvent *ev)
{
    QPoint pos = ev->pos();
    pos.setY(pos.y()-this->menuBar()->geometry().height());


    if(state == ST_MAKING_STEP )
    {

        QPainter painter(this);

        QPoint point = enemyFieldImage->getCoord(pos.x(), pos.y());
        if(point.x()==-1)return;
        qDebug()<<"Ship at "<<point.x()<<point.y();

        bool turn = 1;

        if(turn == 1)
        {
            if(enemyFieldImage->shot(point.x(),point.y()) == 1)
            {
                enemyFieldImage->setCell(point.x(),point.y(),CL_READFULL);
                int count =  enemyFieldImage->sunkShip();

                if(count==20)
                {
                    qDebug()<<"Human wins";
                    chooseDialog->show();
                }

            }
            else
            {
                enemyFieldImage->setCell(point.x(),point.y(),CL_DOT);
                turn = 0;
            }


            enemyFieldImage->redraw();
            this->update();

        }

        if (turn == 0)
        {
            qDebug()<< "Хiд комп'ютера: ";


            int xBot = QRandomGenerator::global()->generate() % N;
            int yBot =  QRandomGenerator::global()->generate() % N;


            qDebug()<<xBot;
            qDebug()<<yBot;


            if(myFieldImage->shot(xBot, yBot))
            {
                myFieldImage->setCell(xBot,yBot,CL_READFULL);

                if(myFieldImage->shot(xBot, yBot) == 1 )
                {

                    if(myFieldImage->shot(xBot, yBot) == 1)
                    {
                        myFieldImage->setCell(xBot,yBot,CL_READFULL);
                        int count =  myFieldImage->sunkShip();
                        if(count==20)
                        {
                            qDebug()<<"Bot wins";
                            chooseDialog->show();
                        }
                    }

                    else
                    {
                        myFieldImage->setCell(xBot,yBot,CL_DOT);
                    }
                }
            }

            else
            {
                myFieldImage->setCell(xBot,yBot,CL_DOT);
            }
            myFieldImage ->redraw();
        }
    }
}

void MainWindow::on_actionStart_triggered()
{
    state = ST_MAKING_STEP;
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
























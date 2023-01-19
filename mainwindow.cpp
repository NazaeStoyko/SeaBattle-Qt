#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"

#include <QPainter>
#include <QRandomGenerator>

#define FIELD_SIZE 10

void MainWindow::startGame()
{
    qDebug()<<"In MainWindow::startGame()";

    myFieldImage->createBoard();
    myFieldImage->redraw();
    enemyFieldImage->createBoard();
    enemyFieldImage->redraw();
    botShipsCount = 20;
    humenShipsCount = 20;
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pictures = new Images();
    pictures->load();

    myFieldImage = new Field(pictures, 40, 39, 216, 217);
    enemyFieldImage = new Field(pictures, 322, 39, 214, 217, true);
    //    chooseDialog = new Choose(this);
    //    connect(chooseDialog, &Choose::accepted, this, &MainWindow::startGame);
    //    connect(chooseDialog, &Choose::accepted, chooseDialog, &Choose::hide);

    startGame();
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


void MainWindow::mousePressEvent(QMouseEvent *ev)
{

    QPoint pos = ev->pos();
    pos.setY(pos.y()-this->menuBar()->geometry().height());

    if(state == ST_MAKING_STEP )
    {
        //        QPainter painter(this);
        QPoint point = enemyFieldImage->getCoord(pos.x(), pos.y());

        if(point.x()==-1)return;

        qDebug()<<"Ship at " << point.x() << point.y();

        if(board->getCellStatus(point.x(), point.y()) == CellStatus::ShipHitted || board->getCellStatus(point.x(), point.y()) == CellStatus::Dot )
        {
            qDebug()<<"Тут вже стріляв!";
            return;
        }
        else if(enemyFieldImage->isHit(point.x(),point.y()))
        {
            board->changeCellStatus(point.x(), point.y(), CellStatus::ShipHitted);
            enemyFieldImage->setCell(point.x(),point.y(),CL_READFULL);
            qDebug()<<"Попали";
            botShipsCount--;
            qDebug()<<botShipsCount;
            if(botShipsCount == 0)
            {
                qDebug()<<"Ви виграли ";
                chooseDialog->show();
            }
        }
        else
        {
            board->changeCellStatus(point.x(), point.y(),CellStatus::Dot);
            enemyFieldImage->setCell(point.x(),point.y(),CL_DOT);
            state = ST_BOT_STEP;
            qDebug()<<"Промах";
        }

        enemyFieldImage->redraw();
        //        this->update();
    }

    while (state == ST_BOT_STEP)
    {
        int xBot;
        int yBot;

        do
        {
            xBot = QRandomGenerator::global()->bounded(0,FIELD_SIZE);
            yBot = QRandomGenerator::global()->bounded(0,FIELD_SIZE);

        }
        while(board->getCellStatus(xBot, yBot) == CellStatus::ShipHitted || board->getCellStatus(xBot, yBot) == CellStatus::Dot);

        if(board->getCellStatus(xBot, yBot) == CellStatus::Ship)
        {
            board->changeCellStatus(xBot, yBot, CellStatus::ShipHitted);
            myFieldImage->setCell(xBot,yBot,CL_READFULL);
            humenShipsCount--;

            if(humenShipsCount == 0)
            {
                qDebug()<<"Бот виграв ";
                chooseDialog->show();
            }
        }

        else if(board->getCellStatus(xBot, yBot) == CellStatus::Empty)
        {
            board->changeCellStatus(xBot, yBot,CellStatus::Dot);
            myFieldImage->setCell(xBot,yBot,CL_DOT);
            state = ST_MAKING_STEP;

        }

        myFieldImage->redraw();
        this->update();
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

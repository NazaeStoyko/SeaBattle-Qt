#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"

#include <QPainter>
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    images = new Images();
    images->load();

    myField = new Field(images, 40, 39, 216, 216);
    enemyField = new Field(images, 322, 39, 216, 216, true);
    chooseDialog = new Choose(this);
    connect(chooseDialog, &Choose::accepted, this, &MainWindow::startGame);
    connect(chooseDialog, &Choose::accepted, chooseDialog, &Choose::hide);
}


MainWindow::~MainWindow()
{
    delete images;
    delete ui;
}


void MainWindow::startGame()
{
    myField->init();
    myField->redraw();
    enemyField->init();
    enemyField->redraw();
    botShipsCount = 20;
    humenShipsCount = 20;
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, this->menuBar()->geometry().height(), images->get("field"));
    painter.drawImage(myField->getX(), this->menuBar()->geometry().height() + myField->getY(), myField->getImage());
    painter.drawImage(enemyField->getX(), this->menuBar()->geometry().height() + enemyField->getY(), enemyField->getImage());
}


void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    QPoint position = ev->pos();
    position.setY(position.y()-this->menuBar()->geometry().height());

    if(gameState == GameState::PLAYER_STEP)
    {
        Coordinate hitCoordinate = enemyField->getCoordinate(position);

        if(hitCoordinate.getRow() == -1) return;

        qDebug()<<"You hit at " << char(hitCoordinate.getColumn() + 65) << hitCoordinate.getRow() + 1;

        if(enemyField->getCellStatus(hitCoordinate) == CellStatus::SHIP_HITTED
                || enemyField->getCellStatus(hitCoordinate) == CellStatus::DOT )
        {
            qDebug()<<"Тут вже стріляв!";
            return;
        }
        else if(enemyField->getCellStatus(hitCoordinate) == CellStatus::SHIP)
        {
            enemyField->setCellStatus(hitCoordinate, CellStatus::SHIP_HITTED);  //CL_READFULL

            botShipsCount--;

            qDebug()<<"Попали. Залишилось кораблів: " << botShipsCount;

            if(botShipsCount == 0)
            {
                qDebug()<<"Ви виграли ";
                chooseDialog->show();
            }
        }
        else
        {
            enemyField->setCellStatus(hitCoordinate,CellStatus::DOT);
            gameState = GameState::BOT_STEP;
            qDebug()<<"Промах";
        }

        enemyField->redraw();
        this->update();
    }

    while (gameState == GameState::BOT_STEP)
    {
        Coordinate botHitCoordinate;
        do
        {
            botHitCoordinate.setRow(QRandomGenerator::global()->bounded(0, BOARD_SIZE));
            botHitCoordinate.setColumn(QRandomGenerator::global()->bounded(0, BOARD_SIZE));
        }
        while(myField->getCellStatus(botHitCoordinate) == CellStatus::SHIP_HITTED
              || myField->getCellStatus(botHitCoordinate) == CellStatus::DOT);

        if(myField->getCellStatus(botHitCoordinate) == CellStatus::SHIP)
        {
            myField->setCellStatus(botHitCoordinate, CellStatus::SHIP_HITTED);
            humenShipsCount--;

            if(humenShipsCount == 0)
            {
                qDebug()<<"Бот виграв ";
                chooseDialog->show();
            }
        }

        else if(myField->getCellStatus(botHitCoordinate) == CellStatus::EMPTY
                || myField->getCellStatus(botHitCoordinate) == CellStatus::SHIP_BORDER)
        {
            myField->setCellStatus(botHitCoordinate, CellStatus::DOT);
            gameState = GameState::PLAYER_STEP;
        }

        myField->redraw();
        this->update();
    }
}


void MainWindow::on_actionStart_triggered()
{
    this->startGame();
    gameState = GameState::PLAYER_STEP;
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

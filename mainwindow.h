#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>
#include <QVector>

#include "images.h"
#include "field.h"
#include "board.h"
#include "choose.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


enum State
{
    ST_PLACING_SHIPS,
    ST_BOT_STEP,
    ST_MAKING_STEP
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev);

private slots:
    void on_actionStart_triggered();
    void on_actionExit_triggered();
    void startGame();

private:
    Ui::MainWindow *ui;
    Images *pictures;
    Field *myFieldImage;
    Field *enemyFieldImage;
    Board *board;
    State state;
    Choose *chooseDialog;
    short int botShipsCount;
    short int humenShipsCount;
};

#endif // MAIN_WINDOW_H

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMouseEvent>
#include <QDebug>
#include <QVector>

#include "images.h"
#include "field.h"
#include "choose.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DifficultyLevel difficultyLevel, QWidget *parent = nullptr);
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
    Images *images;
    Field *myField;
    Field *enemyField;
    GameState gameState;
    Choose *chooseDialog;
    short int botShipsCount;
    short int humenShipsCount;
    DifficultyLevel difficultyLevel = DifficultyLevel::HARD;
};

#endif // MAIN_WINDOW_H

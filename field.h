#pragma once
#include <QVector>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include "images.h"
#include "board.h"
#include "coordinate.h"
#include <QRandomGenerator>

enum Cell
{
    CL_CLEAR = 0,
    CL_SHIP,
    CL_DOT,
    CL_HALF,
    CL_READFULL,
    CL_REDHALL
};


class Field
{
public:
    Field(Images * images , int lft,int tp,int wdth,int hght);
    ~Field();

    const QImage& getImage()const;
    void redraw();
    Cell getCell (int x, int y);
    void setCell(int x,int y, Cell cell);
    QPoint getCoord(int x, int y);

    int getX();
    int getY();
    Board *board;
     bool isEnemy;
    bool shot(int x , int y);
    int sunkShips = 0;
    bool checkShip = false;
    int sunkShip();
    void createBoard();


private:
    QImage *image;
    Images * pictures;
    QVector<Cell> field;
    QVector<Cell> playground;

    int left,top,width,height;


};





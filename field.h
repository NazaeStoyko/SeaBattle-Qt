#ifndef FIELD_H
#define FIELD_H

#include <QVector>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QRandomGenerator>
#include "images.h"
#include "board.h"

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
    Field(Images *images, int left, int top, int width, int height, bool enemy = false);
    ~Field();

    const QImage& getImage()const;
    void redraw();
    Cell getCell (int x, int y);
    void setCell(int x,int y, Cell cell);
    QPoint getCoord(int x, int y);

    int getX();
    int getY();
    Board *board;
    bool isHit(int x , int y);
    int sunkShips = 0;
    void createBoard();

private:
    QImage *image;
    Images *pictures;
    QVector<Cell> field;
    QVector<Cell> playground;

    int left;
    int top;
    int width;
    int height;
    bool enemy;
};

#endif //FIELD_H

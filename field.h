#ifndef FIELD_H
#define FIELD_H

#include <QVector>
#include <QImage>
#include <QPoint>
#include "images.h"
#include "board.h"


class Field
{
public:
    Field(Images *images, int left, int top, int width, int height, bool enemy = false);
    ~Field();
    void init();
    void redraw();
    const QImage& getImage() const;
    Coordinate getCoordinate(QPoint point);
    void setCellStatus(const Coordinate &coordinate, CellStatus cellStatus);
    CellStatus getCellStatus(const Coordinate &coordinate);
    int getX();
    int getY();

private:
    void createBoard();
    QImage *fieldImage;
    Images *images;
    Board *board;
    QVector<CellStatus> playground;

    int left;
    int top;
    int width;
    int height;
    bool enemy;
};

#endif //FIELD_H

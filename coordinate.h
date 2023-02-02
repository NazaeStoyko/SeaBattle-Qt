#ifndef COORDINATE_H
#define COORDINATE_H

#include <QList>

class  Coordinate
{
    short int row;
    short int column;

public:
    Coordinate();
    Coordinate(short int row, short int column);
    void setRow(short row);
    short getRow() const;
    void setColumn(short column);
    short getColumn() const;
    QList<Coordinate> getCornerCellsCoordinates() const;
};

#endif

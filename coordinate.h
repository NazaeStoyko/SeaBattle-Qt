#ifndef COORDINATE_H
#define COORDINATE_H


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
};

#endif

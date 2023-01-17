#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
public:
    short int row;
    short int column;
    int index;  // TODO change into short
    Coordinate();
    Coordinate(short int row, short int column, int index);
};

#endif

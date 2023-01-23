#include "coordinate.h"

Coordinate::Coordinate()
{

}

Coordinate::Coordinate(short int row, short int column)
{
    this->row = row;
    this->column = column;
}

void Coordinate::setRow(short row)
{
    this->row = row;
}

short Coordinate::getRow() const
{
    return row;
}

void Coordinate::setColumn(short column)
{
    this->column = column;
}

short Coordinate::getColumn() const
{
    return column;
}

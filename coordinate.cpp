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

QList<Coordinate> Coordinate::getCornerCellsCoordinates() const
{
    QList<Coordinate> cornerCellsCoordinates(4);
    cornerCellsCoordinates.append(Coordinate(this->row - 1, this->column - 1));
    cornerCellsCoordinates.append(Coordinate(this->row - 1, this->column + 1));
    cornerCellsCoordinates.append(Coordinate(this->row + 1, this->column - 1));
    cornerCellsCoordinates.append(Coordinate(this->row + 1, this->column + 1));
    return cornerCellsCoordinates;
}

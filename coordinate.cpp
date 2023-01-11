#include "coordinate.h"

Coordinate::Coordinate()
{

}

Coordinate::Coordinate(short int row, short int column, int index)
{
    this->row = row;
    this->column = column;
    this->index = index;
}

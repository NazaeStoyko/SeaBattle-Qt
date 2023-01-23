#include "ship.h"

Ship::Ship()
{
    
}

Ship::Ship(Orientation orientation) : orientation(orientation)
{
}

void Ship::clear()
{
    coordinates.clear();
}

int Ship::length() const
{
    return this->coordinates.length();
}

void Ship::append(Coordinate coordinate)
{
    this->coordinates.append(coordinate);
}

void Ship::prepend(Coordinate coordinate)
{
    this->coordinates.prepend(coordinate);
}

Coordinate Ship::getFirst() const
{
    return this->coordinates.constFirst();
}

Coordinate Ship::getLast() const
{
    return this->coordinates.constLast();
}

Orientation Ship::getOrientation() const
{
    return this->orientation;
}

const QList<Coordinate> &Ship::getCoordinatesList() const
{
    return this->coordinates;
}




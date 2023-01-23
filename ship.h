#ifndef SHIP_H
#define SHIP_H

#include "coordinate.h"
#include <QList>

enum class Orientation
{
  HORIZONTAL = 0,
  VERTICAL
};

class Ship
{
    QList<Coordinate> coordinates;
    Orientation orientation;
public:
    Ship();
    Ship(Orientation orientation);
    void clear();
    int length() const;
    void append(Coordinate coordinate);
    void prepend(Coordinate coordinate);
    Coordinate getFirst() const;      // Крайній лівий/верхній сектор корабля
    Coordinate getLast()  const;       // Крайній правий/нижній сектор корабля
    Orientation getOrientation()  const;
    const QList<Coordinate>& getCoordinatesList() const;
};

#endif // SHIP_H

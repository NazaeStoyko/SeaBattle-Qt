#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "coordinate.h"
#include "cellstatus.h"

class Board
{
    QVector<Coordinate> emptyCells;

public:
    CellStatus table[BOARD_SIZE][BOARD_SIZE];  //TODO make it private

    void init();
    void changeCellStatus(short int row, short int column, CellStatus cellStatus);
    void drawShips();
    bool isHit(short int x, short int y);

private:
    void createShips(short int shipLenght, short int shipsCount);
    Coordinate getEmptyCellCoordinate(QVector<Coordinate> &emptyCellsVector);
    void removeCoordinate(short int index);
    short int drawShip(short int shipLenght);
    void setShipBorder(short int shipLenght, Coordinate coordinates);
};

#endif // BOARD_H

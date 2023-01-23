#ifndef BOARD_H
#define BOARD_H

#include "coordinate.h"
#include "cellstatus.h"
#include "ship.h"


class Board
{
    CellStatus table[BOARD_SIZE][BOARD_SIZE];  //TODO make it private

public:
    void init();
    void changeCellStatus(const Coordinate &coordinate, CellStatus cellStatus);
    void changeCellStatus(short int row, short int column, CellStatus cellStatus);
    void placeShipsRandomly();
    bool isHit(Coordinate coordinate);
    bool isHit(short int row, short int column);
    CellStatus getCellStatus(Coordinate coordinate);
    CellStatus getCellStatus(short int row, short int column);

private:
    void createShips(short int shipLenght, short int shipsCount);
    Ship* createShip(short int shipLenght);
    Coordinate getEmptyCellCoordinate();
    void placeShipOnBoard(Ship* ship);
    void drawBoardToConsole();
};

#endif // BOARD_H

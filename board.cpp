#include "board.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QDebug>

void Board::init()
{
    short int index = 0;
    for (short int row = 0; row < BOARD_SIZE; row++)
    {
        for (short int column = 0; column < BOARD_SIZE; column++)
        {
            this->changeCellStatus(row, column, CellStatus::Empty);
            this->emptyCells.push_back(Coordinate(row, column, index));
            ++index;
        }
    }
}


void Board::changeCellStatus(short row, short column, CellStatus cellStatus)
{
    this->table[row][column] = cellStatus;
}


void Board::drawShips()
{
    createShips(4, 1);
    createShips(3, 2);
    createShips(2, 3);
    createShips(1, 4);
}


void Board::createShips(short shipLenght, short shipsCount)
{
    for (short i = 0; i < shipsCount; i++)
    {
        drawShip(shipLenght);
    }
}


short int Board::drawShip(short shipLenght)
{
    bool finish = false;
    Coordinate emptyCellCoordinate;

    while (!finish)
    {
        emptyCellCoordinate = getEmptyCellCoordinate(this->emptyCells);

        int result = 0;

        for (short int index = 0; index < shipLenght; index++)
        {
            if (emptyCellCoordinate.column + index < BOARD_SIZE)
            {
                if (this->table[emptyCellCoordinate.row + index][emptyCellCoordinate.column ] == 0)
                {
                    result += 1;
                }
            }
        }

        if (result == shipLenght)
        {
            removeCellFromEmptyCellVector(emptyCellCoordinate.index);

            finish = true;
        }
    }
    setShipBorder(shipLenght, emptyCellCoordinate);
    return true;
}


Coordinate Board::getEmptyCellCoordinate(QVector<Coordinate> &emptyCellsVector)
{
    short int size = emptyCellsVector.size();
    short int randomIndex = QRandomGenerator::global()->generate() % size;

    return Coordinate(emptyCellsVector[randomIndex].row, emptyCellsVector[randomIndex].column, emptyCellsVector[randomIndex].index);
}


void Board::removeCellFromEmptyCellVector(short index)
{
    this->emptyCells.erase(this->emptyCells.begin() + index);
}


void Board::setShipBorder(short shipLenght, Coordinate coordinates) {

    for (short int index = 0; index < shipLenght; index++)
    {
        changeCellStatus(coordinates.row + index, coordinates.column , CellStatus::Ship);

        if (coordinates.column > 0)
        {
            changeCellStatus(coordinates.row + index, coordinates.column -1, CellStatus::ShipBorder);
        }

        if (coordinates.column < 9)
        {
            changeCellStatus(coordinates.row + index, coordinates.column +1, CellStatus::ShipBorder);
        }
    }

    if (coordinates.row + shipLenght < BOARD_SIZE)
    {
        changeCellStatus(coordinates.row + shipLenght, coordinates.column , CellStatus::ShipBorder);

        if (coordinates.column > 0)
        {
            changeCellStatus(coordinates.row + shipLenght, coordinates.column - 1, CellStatus::ShipBorder);
        }
        if (coordinates.column < 9)
        {
            changeCellStatus(coordinates.row + shipLenght, coordinates.column + 1 , CellStatus::ShipBorder);
        }
    }


    if (coordinates.row > 0)
    {
        changeCellStatus(coordinates.row - 1, coordinates.column , CellStatus::ShipBorder);

        if (coordinates.column > 0)
        {
            changeCellStatus(coordinates.row - 1, coordinates.column - 1, CellStatus::ShipBorder);
        }
        if (coordinates.column < 9)
        {
            changeCellStatus(coordinates.row - 1, coordinates.column + 1, CellStatus::ShipBorder);
        }
    }

}

bool Board::isHit(short x, short y)
{
    return (this->table[x][y] == CellStatus::Ship);
}





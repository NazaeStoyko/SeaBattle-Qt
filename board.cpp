#include "board.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QDebug>


void Board::init()
{
    for (short int row = 0; row < BOARD_SIZE; row++)
    {
        for (short int column = 0; column < BOARD_SIZE; column++)
        {
            this->changeCellStatus(row, column, CellStatus::Empty);
        }
    }
}


void Board::changeCellStatus(short row, short column, CellStatus cellStatus)
{
    if(row >= 0 && row < 10 && column >= 0 && column < 10){
        this->table[row][column] = cellStatus;
    }
}


void Board::placeShipsRandomly()
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
        Ship *newShip = createShip(shipLenght);
        placeShipOnBoard(newShip);
        delete newShip;
    }
}


Ship* Board::createShip(short shipLenght)
{
    Ship* ship = new Ship(Orientation(QRandomGenerator::global()->generate() % 2));

    while (ship->length() != shipLenght)
    {
        ship->clear();
        ship->append(getEmptyCellCoordinate());
        if(ship->length() == shipLenght)
        {
            return ship;
        }
        if(ship->getOrientation() == Orientation::HORIZONTAL)
        {
            bool canAddCellToRight = true;
            while(ship->length() != shipLenght)
            {
                if (canAddCellToRight) {
                    Coordinate nextRigthCell(ship->getLast().row, ship->getLast().column + 1);
                    if((nextRigthCell.column < 10)
                            & (table[nextRigthCell.row][nextRigthCell.column] == CellStatus::Empty))
                    {
                        ship->append(nextRigthCell);
                    } else
                    {
                        canAddCellToRight = false;
                    }
                } else
                {
                    Coordinate nextLeftCell(ship->getFirst().row, ship->getFirst().column - 1);
                    if((nextLeftCell.column > -1)
                            & (table[nextLeftCell.row][nextLeftCell.column] == CellStatus::Empty))
                    {
                        ship->prepend(nextLeftCell);
                    } else
                    {
                        break;
                    }
                }
            }
        } else
        {
            bool canAddCellToBottom = true;
            while(ship->length() != shipLenght)
            {
                if (canAddCellToBottom) {
                    Coordinate nextBottomCell(ship->getLast().row + 1, ship->getLast().column);
                    if((nextBottomCell.row < 10)
                            & (table[nextBottomCell.row][nextBottomCell.column] == CellStatus::Empty))
                    {
                        ship->append(nextBottomCell);
                    } else
                    {
                        canAddCellToBottom = false;
                    }
                } else
                {
                    Coordinate nextTopCell(ship->getFirst().row - 1, ship->getFirst().column);
                    if((nextTopCell.column > -1)
                            & (table[nextTopCell.row][nextTopCell.column] == CellStatus::Empty))
                    {
                        ship->prepend(nextTopCell);
                    } else
                    {
                        break;
                    }
                }
            }
        }
    }
    return ship;
}


Coordinate Board::getEmptyCellCoordinate()
{
    short int randomNumber;
    do
    {
        randomNumber = QRandomGenerator::global()->generate() % 100;
    }
    while (table[randomNumber / 10][randomNumber % 10] != CellStatus::Empty);

    return Coordinate(randomNumber / 10, randomNumber % 10);
}


void Board::placeShipOnBoard(Ship* ship)
{
    Coordinate firstShipCell = ship->getFirst();
    Coordinate lastShipCell = ship->getLast();

    if (ship->getOrientation() == Orientation::HORIZONTAL)
    {
        this->changeCellStatus(firstShipCell.row - 1, firstShipCell.column - 1, CellStatus::ShipBorder);
        this->changeCellStatus(firstShipCell.row, firstShipCell.column - 1, CellStatus::ShipBorder);
        this->changeCellStatus(firstShipCell.row + 1, firstShipCell.column - 1, CellStatus::ShipBorder);

        for (Coordinate coordinate : ship->getCoordinatesList())
        {
            this->changeCellStatus(coordinate.row - 1, coordinate.column, CellStatus::ShipBorder);
            this->changeCellStatus(coordinate.row, coordinate.column, CellStatus::Ship);
            this->changeCellStatus(coordinate.row + 1, coordinate.column, CellStatus::ShipBorder);
        }

        this->changeCellStatus(lastShipCell.row - 1, lastShipCell.column + 1, CellStatus::ShipBorder);
        this->changeCellStatus(lastShipCell.row, lastShipCell.column + 1, CellStatus::ShipBorder);
        this->changeCellStatus(lastShipCell.row + 1, lastShipCell.column + 1, CellStatus::ShipBorder);
    } else
    {
        this->changeCellStatus(firstShipCell.row - 1, firstShipCell.column - 1, CellStatus::ShipBorder);
        this->changeCellStatus(firstShipCell.row - 1, firstShipCell.column, CellStatus::ShipBorder);
        this->changeCellStatus(firstShipCell.row - 1, firstShipCell.column + 1, CellStatus::ShipBorder);

        for (Coordinate coordinate : ship->getCoordinatesList())
        {
            this->changeCellStatus(coordinate.row, coordinate.column - 1, CellStatus::ShipBorder);
            this->changeCellStatus(coordinate.row, coordinate.column, CellStatus::Ship);
            this->changeCellStatus(coordinate.row, coordinate.column + 1, CellStatus::ShipBorder);
        }
        this->changeCellStatus(lastShipCell.row + 1, lastShipCell.column - 1, CellStatus::ShipBorder);
        this->changeCellStatus(lastShipCell.row + 1, lastShipCell.column, CellStatus::ShipBorder);
        this->changeCellStatus(lastShipCell.row + 1, lastShipCell.column + 1, CellStatus::ShipBorder);
    }
}

void Board::drawBoardToConsole()
{
    QString string;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            string.append(QString::number((int)table[j][i]));
        }
        qDebug() << string;
        string.clear();
    }
    qDebug() << " ";
}

bool Board::isHit(short row, short column)
{
    return (this->table[row][column] == CellStatus::Ship);
}

CellStatus Board::getCellStatus(short row, short column)
{
    return this->table[row][column];
}





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
            this->changeCellStatus(row, column, CellStatus::EMPTY);
        }
    }
}


void Board::changeCellStatus(const Coordinate &coordinate, CellStatus cellStatus)
{
    this->changeCellStatus(coordinate.getRow(), coordinate.getColumn(), cellStatus);
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
                    Coordinate nextRigthCell(ship->getLast().getRow(), ship->getLast().getColumn() + 1);
                    if((nextRigthCell.getColumn() < 10)
                            & (table[nextRigthCell.getRow()][nextRigthCell.getColumn()] == CellStatus::EMPTY))
                    {
                        ship->append(nextRigthCell);
                    } else
                    {
                        canAddCellToRight = false;
                    }
                } else
                {
                    Coordinate nextLeftCell(ship->getFirst().getRow(), ship->getFirst().getColumn() - 1);
                    if((nextLeftCell.getColumn() > -1)
                            & (table[nextLeftCell.getRow()][nextLeftCell.getColumn()] == CellStatus::EMPTY))
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
                    Coordinate nextBottomCell(ship->getLast().getRow() + 1, ship->getLast().getColumn());
                    if((nextBottomCell.getRow() < 10)
                            & (table[nextBottomCell.getRow()][nextBottomCell.getColumn()] == CellStatus::EMPTY))
                    {
                        ship->append(nextBottomCell);
                    } else
                    {
                        canAddCellToBottom = false;
                    }
                } else
                {
                    Coordinate nextTopCell(ship->getFirst().getRow() - 1, ship->getFirst().getColumn());
                    if((nextTopCell.getColumn() > -1)
                            & (table[nextTopCell.getRow()][nextTopCell.getColumn()] == CellStatus::EMPTY))
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
    while (table[randomNumber / 10][randomNumber % 10] != CellStatus::EMPTY);

    return Coordinate(randomNumber / 10, randomNumber % 10);
}


void Board::placeShipOnBoard(Ship* ship)
{
    Coordinate firstShipCell = ship->getFirst();
    Coordinate lastShipCell = ship->getLast();

    if (ship->getOrientation() == Orientation::HORIZONTAL)
    {
        this->changeCellStatus(firstShipCell.getRow() - 1, firstShipCell.getColumn() - 1, CellStatus::SHIP_BORDER);
        this->changeCellStatus(firstShipCell.getRow(), firstShipCell.getColumn() - 1, CellStatus::SHIP_BORDER);
        this->changeCellStatus(firstShipCell.getRow() + 1, firstShipCell.getColumn() - 1, CellStatus::SHIP_BORDER);

        for (Coordinate coordinate : ship->getCoordinatesList())
        {
            this->changeCellStatus(coordinate.getRow() - 1, coordinate.getColumn(), CellStatus::SHIP_BORDER);
            this->changeCellStatus(coordinate.getRow(), coordinate.getColumn(), CellStatus::SHIP);
            this->changeCellStatus(coordinate.getRow() + 1, coordinate.getColumn(), CellStatus::SHIP_BORDER);
        }

        this->changeCellStatus(lastShipCell.getRow() - 1, lastShipCell.getColumn() + 1, CellStatus::SHIP_BORDER);
        this->changeCellStatus(lastShipCell.getRow(), lastShipCell.getColumn() + 1, CellStatus::SHIP_BORDER);
        this->changeCellStatus(lastShipCell.getRow() + 1, lastShipCell.getColumn() + 1, CellStatus::SHIP_BORDER);
    } else
    {
        this->changeCellStatus(firstShipCell.getRow() - 1, firstShipCell.getColumn() - 1, CellStatus::SHIP_BORDER);
        this->changeCellStatus(firstShipCell.getRow() - 1, firstShipCell.getColumn(), CellStatus::SHIP_BORDER);
        this->changeCellStatus(firstShipCell.getRow() - 1, firstShipCell.getColumn() + 1, CellStatus::SHIP_BORDER);

        for (Coordinate coordinate : ship->getCoordinatesList())
        {
            this->changeCellStatus(coordinate.getRow(), coordinate.getColumn() - 1, CellStatus::SHIP_BORDER);
            this->changeCellStatus(coordinate.getRow(), coordinate.getColumn(), CellStatus::SHIP);
            this->changeCellStatus(coordinate.getRow(), coordinate.getColumn() + 1, CellStatus::SHIP_BORDER);
        }
        this->changeCellStatus(lastShipCell.getRow() + 1, lastShipCell.getColumn() - 1, CellStatus::SHIP_BORDER);
        this->changeCellStatus(lastShipCell.getRow() + 1, lastShipCell.getColumn(), CellStatus::SHIP_BORDER);
        this->changeCellStatus(lastShipCell.getRow() + 1, lastShipCell.getColumn() + 1, CellStatus::SHIP_BORDER);
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

bool Board::isHit(Coordinate coordinate)
{
    return this->isHit(coordinate.getRow(), coordinate.getColumn());
}


bool Board::isHit(short row, short column)
{
    return (this->table[row][column] == CellStatus::SHIP);
}


CellStatus Board::getCellStatus(Coordinate coordinate)
{
    return this->getCellStatus(coordinate.getRow(), coordinate.getColumn());
}


CellStatus Board::getCellStatus(short row, short column)
{
    return this->table[row][column];
}



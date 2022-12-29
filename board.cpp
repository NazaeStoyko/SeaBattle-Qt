#include "board.h"
#include <QPainter>
#include <QRandomGenerator>
#include "board.h"
#include <QDebug>

void Board::init()
{

    size_t index = 0;
    for (short int row = 0; row < LENGHT; row++)
    {
        for (short int column = 0; column < LENGHT; column++)
        {
            this->draw(row, column, 0);

            this->empty.push_back(Coordinate(row, column, index));
            index += 1;
        }
    }

}

void Board::draw(short row, short column, short value)
{
    this->table[row][column] = value;
}

Coordinate Board::getEmptyCoordinate(QVector<Coordinate> vec)
{
    short int size = vec.size();
    size_t index = QRandomGenerator::global()->generate() % size;
    short int row = vec[index].row;
    short int column = vec[index].column;

    return Coordinate(row, column, index);

}

void Board::removeCoordinate(size_t index)
{
    this->empty.erase(this->empty.begin() + index);
}


short int  Board::drawShip(short shipLenght)
{
    bool finish = false;
    Coordinate coordinates = Coordinate(0,0,0);
    QVector<Coordinate> cloned = this->empty;

    while (finish == false)
    {
        coordinates = getEmptyCoordinate(cloned);

        cloned.erase(cloned.begin() + index);

        int result = 0;


        for (size_t index = 0; index < shipLenght; index++)
        {
            if (coordinates.column + index < LENGHT)
            {
                if (this->table[coordinates.row + index][coordinates.column ] == 0)
                {

                    result += 1;
                }
            }
        }

        if (result == shipLenght)
        {
            removeCoordinate(coordinates.index);

            finish = true;
        }
    }
    borderShip(shipLenght, coordinates);
    return true;
}


void Board::borderShip(short shipLenght, Coordinate coordinates) {

    for (size_t index = 0; index < shipLenght; index++)
    {
        draw(coordinates.row + index, coordinates.column , 1);

        if (coordinates.column > 0)
        {
            draw(coordinates.row + index, coordinates.column -1, 2);
        }

        if (coordinates.column < 9)
        {
            draw(coordinates.row + index, coordinates.column +1, 2);
        }
    }

    if (coordinates.row + shipLenght < LENGHT)
    {
        draw(coordinates.row + shipLenght, coordinates.column , 2);

        if (coordinates.column > 0)
        {
            draw(coordinates.row + shipLenght, coordinates.column - 1, 2);
        }
        if (coordinates.column < 9)
        {
            draw(coordinates.row + shipLenght, coordinates.column + 1 ,2);
        }
    }


    if (coordinates.row > 0)
    {
        draw(coordinates.row - 1, coordinates.column , 2);

        if (coordinates.column > 0)
        {
            draw(coordinates.row - 1, coordinates.column - 1, 2);
        }
        if (coordinates.column < 9)
        {
            draw(coordinates.row - 1, coordinates.column + 1, 2);
        }
    }

}


void Board::createShip(int lenght, int count)
{
    for (int i = 0; i < count; i++)
    {
        drawShip(lenght);
    }
}

void Board::drawShips()
{

    createShip(4, 1);
    createShip(3, 2);
    createShip(2, 3);
    createShip(1, 4);
}


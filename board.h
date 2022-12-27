#ifndef BOARD_H
#define BOARD_H
#include "coordinate.h"
#include <QVector>
#include <QPainter>


const int LENGHT = 10;

class Board
{

public:
    short int table[LENGHT][LENGHT];
    QVector<Coordinate> empty{};
    int index = 0;

    void draw(short int row, short int column, short int value);
    void init();
    Coordinate getEmptyCoordinate(QVector<Coordinate> vec);
    void removeCoordinate(size_t index);
    void drawTable();
    short int drawShip(short int  shipLenght);
    void borderShip(short int shipLenght, Coordinate coordinates);
    void createShip(int lenght, int count);
    void drawShips();


};

#endif // BOARD_H



























#include "field.h"

#include <QRandomGenerator>
#include <QPainter>
#include <QDebug>


Field::Field(Images* images , int left , int top , int width, int height, bool enemy):
    images(images), left(left), top(top), width(width), height(height), enemy(enemy)
{
    fieldImage = new QImage(width, height, QImage::Format_ARGB32);
    board = new Board();
    this->init();
}


Field::~Field()
{
    delete fieldImage;
    delete board;
}

void Field::init()
{
    this->createBoard();
}


void Field::createBoard()
{
    board->init();
    board->placeShipsRandomly();
}


const QImage& Field::getImage() const
{
    return *fieldImage;
}


void Field::redraw()
{
    fieldImage->fill(0);

    QPainter painter(fieldImage);
    double cfx = 1.0 * width / 10.0;
    double cfy = 1.0 * height / 10.0;

    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            switch (board->getCellStatus(j, i))
            {
            case CellStatus::DOT:
                painter.drawImage(i * cfx, j * cfy, images->get("dot"));
                break;

            case CellStatus::SHIP_HITTED:
                painter.drawImage(i * cfx, j * cfy,images->get("redfull"));
                break;

            case CellStatus::SHIP:
                if (!this->enemy)
                {
                    painter.drawImage(i * cfx, j * cfy, images->get("full"));
                }
                break;
            default:
                break;
            }
        }
    }
}


CellStatus Field::getCellStatus(const Coordinate &coordinate)
{
    return board->getCellStatus(coordinate);
}


void Field::setCellStatus(const Coordinate &coordinate, CellStatus cellStatus)
{
    this->board->changeCellStatus(coordinate, cellStatus);
}


int Field::getX()
{
    return left;
}

int Field::getY()
{
    return top;
}


Coordinate Field::getCoordinate(QPoint point)
{
    Coordinate coordinate;
    coordinate.setRow(-1);
    coordinate.setColumn(-1);

    if(point.x() < left || point.x() > (left+width) || point.y() < top || point.y() > (top + height)) return coordinate;

    double cfx = 1.0 * width/10.0;
    double cfy = 1.0 * height/10.0;

    coordinate.setRow(1.0 * (point.y() - top) / cfy);
    coordinate.setColumn(1.0 * (point.x() - left) / cfx);

    return coordinate;
}

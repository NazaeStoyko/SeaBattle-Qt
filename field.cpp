#include "field.h"
#include <QRandomGenerator>
#include <board.h>

void Field::createBoard()
{

    board->init();
    board->drawShips();

}

Field::Field(Images* images , int lft , int tp , int wdth,int hgh):
    pictures(images),left(lft), top(tp), width(wdth), height(hgh)
{
    isEnemy = false;

    field.fill(CL_CLEAR,100);

    playground.fill(CL_CLEAR, 100);

    image = new QImage (width , height,QImage::Format_ARGB32);
    board = new Board();
}




Field::~Field()
{
    delete image;
}

const QImage& Field::getImage()const
{
    return *image;
}



void Field::redraw()
{
    image->fill(0);


    QPainter painter(image);
    double cfx = 1.0*width/10.0;
    double cfy = 1.0*height/10.0;

    for (int i = 0; i < 10; i++)
    {
        for(int j=0; j<10;j++)
        {

            if(board->table[i][j] == 1 && !isEnemy){
                painter.drawImage(i*cfx,j*cfy,pictures->get("full"));
            }


            switch (getCell(i,j))
            {
            case CL_DOT:
                painter.drawImage(i*cfx,j*cfy,pictures->get("dot"));

                break;

            case CL_HALF:

                painter.drawImage(i*cfx,j*cfy,pictures->get("half"));
                break;

            case CL_SHIP:

                painter.drawImage(i*cfx, j*cfy, pictures->get("full"));
                break;

            case CL_READFULL:
                painter.drawImage(i*cfx,j*cfy,pictures->get("redhalf"));
                break;
            default:
                break;
            }

        }

    }

}

bool Field::isHit(int x , int y)
{
    QPainter painter(image);

    return (board->table[x][y] == 1);
}


//int Field ::sunkShip()
//{
//sunkShips +=1;
//return sunkShips;
//}

Cell Field ::getCell(int x , int y)
{
    int n = y*10+x;
    if(n>=0 && n<playground.size())
        return playground[n];

    qDebug()<<"Error: no sush cell";
    return CL_CLEAR;
}

void Field::setCell(int x,int y,Cell cell)
{
    int n = y*10+x;

    if(n>=0 && n<field.size())
    {
        if(field[n] == CL_CLEAR) {
            playground[n] = cell;
        }
        else {
            playground[n] = field[n];
        }
        return;
    }
    qDebug()<<"Error: no such cell";
}

int Field::getX()
{
    return left;
}

int Field::getY()
{
    return top;
}

QPoint Field::getCoord(int x,int y)
{
    QPoint res;
    res.setX(-1);
    res.setY(-1);
    if(x<left || x>(left+width) || y<top || y>(top+height)) return res;

    double cfx = 1.0*width/10.0;
    double cfy = 1.0*width/10.0;

    res.setX(1.0*(x-left)/cfx);
    res.setY(1.0*(y-top)/cfy);
    return res;

}

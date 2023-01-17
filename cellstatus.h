#ifndef CELLSTATUS_H
#define CELLSTATUS_H

#define BOARD_SIZE 10

enum CellStatus{
    Empty = 0,
    Ship,
    ShipBorder,
    ShipHitted,
    Dot
};

#endif // CELLSTATUS_H

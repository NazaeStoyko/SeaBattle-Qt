#ifndef CELLSTATUS_H
#define CELLSTATUS_H

#define BOARD_SIZE 10

enum class CellStatus{
    EMPTY = 0,
    SHIP,
    SHIP_BORDER,
    SHIP_HITTED,
    DOT
};

#endif // CELLSTATUS_H

#ifndef ENUMS_H
#define ENUMS_H

#define BOARD_SIZE 10

enum class GameState
{
    PLACING_SHIPS,
    PLAYER_STEP,
    BOT_STEP
};

enum class CellStatus {
    EMPTY = 0,
    SHIP,
    SHIP_BORDER,
    SHIP_HITTED,
    SUNK_SHIP_BORDER,
    DOT,

};

enum class DifficultyLevel {
    NORMAL,
    HARD
};

#endif // ENUMS_H

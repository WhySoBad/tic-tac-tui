#ifndef TIC_TAC_TUI_COMPUTER_H
#define TIC_TAC_TUI_COMPUTER_H

#include "Player.h"
#include "Board.h"

#define COMPUTER_MOVE_SPEED     150

class Computer: public Player {
    Board *board;
public:

    /**
     * Pick a field to compete against the player
     */

    void pickField();

    Computer(Board *board, unsigned char id, ConsoleColor color, const char *character, bool outlined);
};


#endif //TIC_TAC_TUI_COMPUTER_H

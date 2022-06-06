#include "Computer.h"
#include "iostream"
#include "thread"
#include "chrono"

Computer::Computer(Board *board, unsigned char id, ConsoleColor color, const char *character, bool outlined) : Player(id, color, character, outlined) {
    this->board = board;
}

void Computer::pickField() {
    int field = 0;
    for (int i = 0; i < board->getFields().size(); ++i) {
        if(board->getFields()[i] == UNOCCUPIED) {
            field = i;
            break;
        }
    }
    int deltaX = field % COLUMNS - board->getSelected() % COLUMNS;
    int deltaY = field / COLUMNS - board->getSelected() / COLUMNS;

    // move to the field and select it

    // movement on the x-axis
    for (int i = 0; i < std::abs(deltaX); ++i) {
        int newField = board->getSelected() + deltaX / std::abs(deltaX);
        board->selectField(newField, this->getColor());
        std::this_thread::sleep_for(std::chrono::milliseconds(COMPUTER_MOVE_SPEED));
        fflush(stdout);
    }

    // movement on the y-axis
    for (int i = 0; i < std::abs(deltaY); ++i) {
        int newField = board->getSelected() + (deltaY / std::abs(deltaY)) * COLUMNS;
        board->selectField(newField, this->getColor());
        std::this_thread::sleep_for(std::chrono::milliseconds(COMPUTER_MOVE_SPEED));
        fflush(stdout);
    }

    board->confirmSelection(this);
}

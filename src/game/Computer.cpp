#include "vector"
#include "Computer.h"
#include "iostream"
#include "thread"
#include "chrono"
#include "random"

inline std::mt19937 &generator() {
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

Computer::Computer(Board *board, unsigned char id, ConsoleColor color, const char *character, bool outlined) : Player(id, color, character, outlined) {
    this->board = board;
}

void Computer::pickField() {
    auto checkForWinnable = [this](int id) -> unsigned int* {
        bool same;
        unsigned char player;
        unsigned int *field = nullptr;
        int empty;

        // check for horizontal fields
        for (int i = 0; i < ROWS; ++i) {
            player = board->getFieldOwner(i * ROWS);
            if(player != UNOCCUPIED && player != id) continue; // this row isn't from interest
            empty = 1; // how many empty are still available for this row

            for (int j = 1; j < COLUMNS; ++j) {
                unsigned char current = board->getFieldOwner(i * COLUMNS + j);
                if(player == UNOCCUPIED && current != UNOCCUPIED) {
                    player = current;
                    empty--;
                    field = new unsigned int(i * ROWS);
                    same = true;
                } else if(player == UNOCCUPIED && current == UNOCCUPIED) { same = false; break; }
                else {
                    same = current == player;
                    if(empty && !same && current == UNOCCUPIED) { empty--; field = new unsigned int(i * COLUMNS + j); same = true; }
                    else if(!same) break;
                }
            }
            if(same && field && !empty) return field;
        }

        // check for vertical fields
        for (int i = 0; i < COLUMNS; ++i) {
            player = board->getFieldOwner(i /** COLUMNS*/);
            if(player != UNOCCUPIED && player != id) continue; // this column isn't from interest
            empty = 1; // how many empty are still available for this column
            for (int j = 1; j < ROWS; ++j) {
                unsigned char current = board->getFieldOwner(i + COLUMNS * j);
                if(player == UNOCCUPIED && current != UNOCCUPIED && empty) {
                    player = current;
                    empty--;
                    field = new unsigned int(i);
                    same = true;
                } else if(player == UNOCCUPIED && current == UNOCCUPIED) { same = false; break; }
                else {
                    same = current == player;
                    if(empty && !same && current == UNOCCUPIED) { empty--; field = new unsigned int(i + COLUMNS * j); same = true; }
                    else if(!same) break;
                }
            }
            if(same && field && !empty) return field;
        }

        if(ROWS != COLUMNS) return nullptr; // there isn't a center field

        // check in descending diagonal
        player = board->getFieldOwner(0);
        empty = 1;
        for (int i = 1; i < COLUMNS; ++i) {
            unsigned char current = board->getFieldOwner(i * COLUMNS + i);
            if(player == UNOCCUPIED && current != UNOCCUPIED && empty) {
                player = current;
                empty--;
                same = true;
                field = new unsigned int(0);
            } else {
                same = current == player;
                if(!same && empty && current == UNOCCUPIED) { empty--; field = new unsigned int(i * COLUMNS + i); same = true; }
                else if(!same) break;
            }
        }
        if(same && field && !empty) return field;

        // check in ascending diagonal
        player = board->getFieldOwner(ROWS * COLUMNS - COLUMNS);
        empty = 1;
        for (int i = 1; i < ROWS; ++i) {
            unsigned char current = board->getFieldOwner(ROWS * COLUMNS - COLUMNS - i * ROWS + i);
            if(player == UNOCCUPIED && current != UNOCCUPIED && empty) {
                player = current;
                empty--;
                same = true;
                field = new unsigned int(ROWS * COLUMNS - COLUMNS);
            } else {
                same = current == player;
                if(!same && empty && current == UNOCCUPIED) { empty--; field = new unsigned int(ROWS * COLUMNS - COLUMNS - i * ROWS + i); same = true; }
                else if(!same) break;
            }
        }
        if(same && field && !empty) return field;
        return nullptr;
    };

    unsigned int *field = checkForWinnable(this->getId());
    ConsoleHelper::moveCursor(0, BOARD_HEIGHT);
    if(!field) field = checkForWinnable(this->getId() == PLAYER_1 ? PLAYER_2 : PLAYER_1);
    if(!field) {
        std::vector<unsigned int> empty = {};
        for (unsigned int i = 0; i < board->getFields().size(); ++i) {
            if(board->getFields()[i] == UNOCCUPIED) empty.push_back(i);
        }
        auto distribution = std::uniform_int_distribution<int>(0, empty.size() - 1);
        field = new unsigned int(empty[distribution(generator())]);
    }

    int deltaX = *field % COLUMNS - board->getSelected() % COLUMNS;
    int deltaY = *field / COLUMNS - board->getSelected() / COLUMNS;

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

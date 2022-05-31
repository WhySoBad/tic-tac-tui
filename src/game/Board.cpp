#include "Board.h"
#include "../screen/ConsoleHelper.h"

Board::Board() {
    for (int i = 0; i < ROWS * COLUMNS; ++i) fields[i] = UNOCCUPIED;
}

std::array<unsigned char, ROWS * COLUMNS> Board::getFields() {
    return fields;
}

bool Board::isFieldEmpty(unsigned char field) {
    return getFieldOwner(field) == UNOCCUPIED;
}

void Board::occupyField(unsigned char field, bool player) {
    if(field >= 0 && field < fields.size() && fields[field] == UNOCCUPIED) {
        fields[field] = player;
        winner = checkForWinner();
    }
}

unsigned char Board::getFieldOwner(unsigned char field) {
    if(field >= 0 && field < fields.size()) return fields[field];
    else return UNOCCUPIED;
}

unsigned char Board::checkForWinner() {
    bool same = true;
    unsigned char player;

    // check for winner in rows
    // 1 1 1
    // 0 0 0
    // 0 0 0

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if(j == 0) {
                player = fields[i * ROWS];
                if(player == UNOCCUPIED) break;
            }
            same = fields[i * ROWS + j] == player;
            if(!same) break;
        }
        if(same && player != UNOCCUPIED) return player;
    }

    // check for winner in columns
    // 1 0 0
    // 1 0 0
    // 1 0 0

    for (int i = 0; i < COLUMNS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            if(j == 0) {
                player = fields[i * COLUMNS];
                if(player == UNOCCUPIED) break;
            }
            same = fields[i + ROWS * j] == player;
            if(!same) break;
        }
        if(same && player != UNOCCUPIED) return player;
    }

    if(fields[(ROWS * COLUMNS - 1) / 2] == UNOCCUPIED || ROWS != COLUMNS) return UNOCCUPIED; // center field isn't occupied or there isn't a center field

    player = fields[0];

    // check for winner in descending diagonal
    // 1 0 0
    // 0 1 0
    // 0 0 1

    if(player != UNOCCUPIED) {
        for (int i = 1; i < COLUMNS; ++i) {
            same = fields[i * COLUMNS + i] == player;
            if(!same) break;
        }
        if(same) return player;
    }

    player = fields[ROWS * COLUMNS - COLUMNS + 1];

    // check for winner in ascending diagonal
    // 0 0 1
    // 0 1 0
    // 1 0 0

    if(player != UNOCCUPIED) {
        for (int i = 1; i < ROWS; ++i) {
            same = fields[ROWS * COLUMNS - COLUMNS + 1 - i * ROWS + i] == player;
            if(!same) break;
        }
        if(same) return player;
    }

    return UNOCCUPIED;
}

unsigned char Board::getWinner() const {
    return winner;
}

void Board::drawBoard() {
    ConsoleHelper::drawEmptyBoard(x, y);

    auto fillField = [](int id, const char * character) {
        int column = id % (ROWS * COLUMNS);
        int row = id / (ROWS * COLUMNS);

    };
}

unsigned short Board::getX() const {
    return x;
}

unsigned short Board::getY() const {
    return y;
}

void Board::setX(unsigned short x) {
    Board::x = x;
}

void Board::setY(unsigned short y) {
    Board::y = y;
}


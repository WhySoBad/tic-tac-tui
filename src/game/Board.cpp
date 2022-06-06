#include "iostream"
#include "string"
#include "Board.h"

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
                player = fields[i];
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

    player = fields[ROWS * COLUMNS - COLUMNS];

    // check for winner in ascending diagonal
    // 0 0 1
    // 0 1 0
    // 1 0 0

    if(player != UNOCCUPIED) {
        for (int i = 1; i < ROWS; ++i) {
            same = fields[ROWS * COLUMNS - COLUMNS - i * ROWS + i] == player;
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
    ConsoleHelper::drawEmptyBoard();
    fflush(stdout);
}

void Board::fillField(int id, const char *character, bool outlined, ConsoleColor color) {
    int column = id % COLUMNS;
    int row = id / COLUMNS;

    int startX = column * (CELL_WIDTH + 1) + 3;
#ifdef _WIN32
    startX -= 1;
#endif
    int startY = row * (CELL_HEIGHT + 1) + 1;

    for (int i = 0; i < CELL_HEIGHT; ++i) {
        ConsoleHelper::moveCursor(startX, startY + i);
        ConsoleHelper::useColor(color);
        if(outlined && !(i == 0 || i == CELL_HEIGHT - 1)) {
            ConsoleHelper::print(character);
            ConsoleHelper::useColor(C_RESET);
            ConsoleHelper::moveCursor(startX + CELL_CONTENT - 1, startY + i);
            ConsoleHelper::useColor(color);
            ConsoleHelper::print(character);
        } else for (int j = 0; j < CELL_CONTENT; ++j) ConsoleHelper::print(character);;
        ConsoleHelper::useColor(C_RESET);
    }
}

void Board::highlightField(int id, ConsoleColor color) {
    int column = id % COLUMNS;
    int row = id / COLUMNS;

    int startX = column * (CELL_WIDTH + 1) + 1;
#ifdef _WIN32
    startX -= 1;
#endif
    int startY = row * (CELL_HEIGHT + 1);

    std::string fieldTop = std::to_string(id);
    std::string fieldBottom = (id / COLUMNS) == (ROWS - 1) ? HORIZONTAL_BORDER : std::to_string(id + COLUMNS);

    ConsoleHelper::moveCursor(startX, startY);
    for (int i = 0; i < CELL_WIDTH + 2; ++i) {
        ConsoleHelper::useColor(color);
        if(i == 0) {
            if(column == 0 && row == 0) ConsoleHelper::print(TOP_LEFT_CORNER);
            else if(column == 0) ConsoleHelper::print(LEFT_CROSSING_BORDER);
            else if(row == 0) ConsoleHelper::print(TOP_CROSSING_BORDER);
            else ConsoleHelper::print(CROSSING_BORDER);
        } else if(i == (CELL_WIDTH + 1)) {
            if(column == COLUMNS - 1 && row == 0) ConsoleHelper::print(TOP_RIGHT_CORNER);
            else if(column == COLUMNS - 1) ConsoleHelper::print(RIGHT_CROSSING_BORDER);
            else if(row == 0) ConsoleHelper::print(TOP_CROSSING_BORDER);
            else ConsoleHelper::print(CROSSING_BORDER);
        } else if((i - 2) % CELL_WIDTH == 0) ConsoleHelper::print(fieldTop.c_str());
        else ConsoleHelper::print(HORIZONTAL_BORDER);
        ConsoleHelper::useColor(C_RESET);
    }

    ConsoleHelper::moveCursor(startX, startY + CELL_HEIGHT + 1);
    for (int i = 0; i < CELL_WIDTH + 2; ++i) {
        ConsoleHelper::useColor(color);
        if(i == 0) {
            if(column == 0 && row == ROWS - 1) ConsoleHelper::print(BOTTOM_LEFT_CORNER);
            else if(column == 0) ConsoleHelper::print(LEFT_CROSSING_BORDER);
            else if(row == ROWS - 1) ConsoleHelper::print(BOTTOM_CROSSING_BORDER);
            else ConsoleHelper::print(CROSSING_BORDER);
        } else if(i == (CELL_WIDTH + 1)) {
            if(column == COLUMNS - 1 && row == ROWS - 1) ConsoleHelper::print(BOTTOM_RIGHT_CORNER);
            else if(column == COLUMNS - 1) ConsoleHelper::print(RIGHT_CROSSING_BORDER);
            else if(row == ROWS - 1) ConsoleHelper::print(BOTTOM_CROSSING_BORDER);
            else ConsoleHelper::print(CROSSING_BORDER);
        } else if((i - 2) % CELL_WIDTH == 0) ConsoleHelper::print(fieldBottom.c_str());
        else ConsoleHelper::print(HORIZONTAL_BORDER);
        ConsoleHelper::useColor(C_RESET);
    }

    for (int i = 0; i < CELL_HEIGHT; ++i) {
        ConsoleHelper::moveCursor(startX, startY + 1 + i);
        ConsoleHelper::useColor(color);
        ConsoleHelper::print(VERTICAL_BORDER);
        ConsoleHelper::useColor(C_RESET);
        ConsoleHelper::moveCursor(startX + CELL_WIDTH + 1, startY + 1 + i);
        ConsoleHelper::useColor(color);
        ConsoleHelper::print(VERTICAL_BORDER);
        ConsoleHelper::useColor(C_RESET);
    }
}

void Board::selectField(int id, ConsoleColor color, bool single) {
    if(selected >= 0 && single) highlightField(selected);
    selected = id;
    if(selected < 0 || selected >= fields.size()) return;
    highlightField(selected, fields[selected] == UNOCCUPIED ? color : FG_BLACK);
}

void Board::confirmSelection(Player *player) {
    if(player->getId() != PLAYER_1 && player->getId() != PLAYER_2) return;
    if(selected < 0 || selected >= fields.size() || fields[selected] != 2) return;
    fields[selected] = player->getId();
    winner = checkForWinner();
    fillField(selected, player->getCharacter(), player->isOutlined(), player->getColor());
    selectField(selected);
}

int Board::getSelected() const {
    return selected;
}

bool Board::isBoardFull() const {
    for (int i = 0; i < fields.size(); ++i) { if(fields[i] == 2) return false; }
    return true;
}

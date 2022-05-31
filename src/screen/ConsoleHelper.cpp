#include "ConsoleHelper.h"
#include "iostream"
#include "../game/Board.h"

void ConsoleHelper::clearTerminal() {
    printf("\x1b[3J");
}

void ConsoleHelper::moveCursor(short x, short y) {
#ifdef _WIN32
    SetConsoleCursorPosition(WindowsConsoleHelper::getHandle(), {x, y});
#else
#ifdef __linux__
    y += LinuxConsoleHelper::getStartLine();
#endif
    printf("\x1b[%i;%iH", y, x);
#endif
}

void ConsoleHelper::writeCharsAt(short x, short y, const char *characters) {
    ConsoleHelper::moveCursor(x, y);
    std::cout << characters;
}

void ConsoleHelper::drawEmptyBoard(short x, short y) {
    int cell = 0;

    auto horizontalLine = [&cell](int mode = 0) {
        const char * first = LEFT_CROSSING_BORDER;
        const char * last = RIGHT_CROSSING_BORDER;
        if(mode == 1) { // top line
            first = TOP_LEFT_CORNER;
            last = TOP_RIGHT_CORNER;
        } else if(mode == 2) { // bottom line
            first = BOTTOM_LEFT_CORNER;
            last = BOTTOM_RIGHT_CORNER;
        }

        bool blocked = false;

        for (int i = 0; i < BOARD_WIDTH; ++i) {
            if(blocked) { blocked = false; continue; }
            if(i == 0) std::cout << first;
            else if(i == BOARD_WIDTH - 1) std::cout << last;
            else if((i - 2) % (CELL_WIDTH + 1) == 0 && i < BOARD_WIDTH - 2 && mode != 2) {
                std::cout << cell;
                cell++;
                blocked = cell > 10;
            }
            else if(i % (CELL_WIDTH + 1) == 0) {
                if(mode == 1) std::cout << TOP_CROSSING_BORDER;
                else if(mode == 2) std::cout << BOTTOM_CROSSING_BORDER;
                else std::cout << CROSSING_BORDER;
            } else std::cout << HORIZONTAL_BORDER;
        }
        std::cout << std::endl;
    };
    
    auto line = []() {
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            if(i % (CELL_WIDTH + 1) == 0) std::cout << VERTICAL_BORDER;
            else std::cout << " ";
        }
        std::cout << std::endl;
    };


    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        if(i % (CELL_HEIGHT + 1) == 0) {
            if(i == 0) horizontalLine(1);
            else if(i == BOARD_HEIGHT - 1) horizontalLine(2);
            else horizontalLine();
        } else line();
    }
}

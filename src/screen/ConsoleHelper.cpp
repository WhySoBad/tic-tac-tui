#include "cstring"
#include "ConsoleHelper.h"
#include "iostream"
#include "../game/Board.h"

void ConsoleHelper::clearTerminal() {
    ConsoleHelper::moveCursor(0, 0);
    printf("\x1b[3J");
}

void ConsoleHelper::moveCursor(short x, short y) {
#ifdef _WIN32
    SetConsoleCursorPosition(WindowsConsoleHelper::getHandle(), {x, y});
#endif
#ifdef __linux__
    int deltaY = y - cursorY;
    if(deltaY < 0 && std::abs(deltaY) > cursorY) deltaY = -cursorY;
    cursorY += deltaY;
    // printf("%i %i %i %i\n", deltaX, deltaY, cursorX, cursorY);
    // printf("\x1b[%i%s\x1b[%i%s", deltaX, deltaX < 0 ? "D" : "C", deltaY, deltaY < 0 ? "A" : "B");
    printf("\x1b[%i;%iH", y + LinuxConsoleHelper::getStartLine() + 1, x);
#endif
}

void ConsoleHelper::print(const char * characters) {
    printf("%s", characters);
}

void ConsoleHelper::writeCharsAt(short x, short y, const char *characters) {
    ConsoleHelper::moveCursor(x, y);
    std::cout << characters;
}

void ConsoleHelper::drawEmptyBoard() {
    int cell = 0;
    ConsoleHelper::moveCursor(0, 0);

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
            if(i == 0) ConsoleHelper::print(first);
            else if(i == BOARD_WIDTH - 1) ConsoleHelper::print(last);
            else if((i - 2) % (CELL_WIDTH + 1) == 0 && i < BOARD_WIDTH - 2 && mode != 2) {
                ConsoleHelper::print(std::to_string(cell).c_str());
                cell++;
                blocked = cell > 10;
            }
            else if(i % (CELL_WIDTH + 1) == 0) {
                if(mode == 1) ConsoleHelper::print(TOP_CROSSING_BORDER);
                else if(mode == 2) ConsoleHelper::print(BOTTOM_CROSSING_BORDER);
                else ConsoleHelper::print(CROSSING_BORDER);
            } else ConsoleHelper::print(HORIZONTAL_BORDER);
        }
#ifdef _WIN32
        ConsoleHelper::print("\n");
#else
        ConsoleHelper::moveCursor(0, cursorY + 1);
#endif
    };
    
    auto line = []() {
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            if(i % (CELL_WIDTH + 1) == 0) ConsoleHelper::print(VERTICAL_BORDER);
            else ConsoleHelper::print(" ");
        }
    #ifdef _WIN32
            ConsoleHelper::print("\n");
    #else
            ConsoleHelper::moveCursor(0, cursorY + 1);
    #endif
    };


    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        if(i % (CELL_HEIGHT + 1) == 0) {
            if(i == 0) horizontalLine(1);
            else if(i == BOARD_HEIGHT - 1) horizontalLine(2);
            else horizontalLine();
        } else line();
    }
}

void ConsoleHelper::initialize() {
#ifdef __linux__
    cursorY = LinuxConsoleHelper::getStartLine();
#endif
}

void ConsoleHelper::showCursor() {
    ConsoleHelper::print("\x1b[?25h");
}

void ConsoleHelper::hideCursor() {
    ConsoleHelper::print("\x1b[?25l");
}

GameKey ConsoleHelper::getKey() {
#ifdef _WIN32
    return static_cast<GameKey>(WindowsConsoleHelper::getKey());
#endif
#ifdef __linux__
    return static_cast<GameKey>(LinuxConsoleHelper::getKey());
#endif
}


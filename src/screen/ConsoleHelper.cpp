#include "cstring"
#include "ConsoleHelper.h"
#include "iostream"
#include "../game/Board.h"

void ConsoleHelper::clearTerminal() {
    ConsoleHelper::moveCursor(0, 0);
    printf("\x1b[3J");
}

void ConsoleHelper::moveCursor(short x, short y) {
    int deltaY = y - cursorY;
    if(deltaY < 0 && std::abs(deltaY) > cursorY) deltaY = -cursorY;
    cursorY += deltaY;
#ifdef _WIN32
    SetConsoleCursorPosition(WindowsConsoleHelper::getHandle(), {x, static_cast<SHORT>(y + WindowsConsoleHelper::getStartLine())});
#endif
#ifdef __linux__
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
#ifdef __linux__
        printf("\n");
#endif
#ifdef _WIN32
        ConsoleHelper::moveCursor(0, cursorY + 1);
#endif
    };
    
    auto line = []() {
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            if(i % (CELL_WIDTH + 1) == 0) ConsoleHelper::print(VERTICAL_BORDER);
            else ConsoleHelper::print(" ");
        }
#ifdef __linux__
        printf("\n");
#endif
#ifdef _WIN32
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

    fflush(stdout);
}

void ConsoleHelper::initialize() {
#ifdef __linux__
    cursorY = LinuxConsoleHelper::getStartLine();
#endif
#ifdef _WIN32
    cursorY = WindowsConsoleHelper::getStartLine();
#endif
}

void ConsoleHelper::showCursor() {
#ifdef __linux__
    ConsoleHelper::print("\x1b[?25h");
    fflush(stdout);
#endif
#ifdef _WIN32
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(WindowsConsoleHelper::getHandle(), &info);
    info.bVisible = TRUE;
    SetConsoleCursorInfo(WindowsConsoleHelper::getHandle(), &info);
#endif
}

void ConsoleHelper::hideCursor() {
#ifdef __linux__
    ConsoleHelper::print("\x1b[?25l");
    fflush(stdout);
#endif
#ifdef _WIN32
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(WindowsConsoleHelper::getHandle(), &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(WindowsConsoleHelper::getHandle(), &info);
#endif
}

GameKey ConsoleHelper::getKey() {
#ifdef _WIN32
    return static_cast<GameKey>(WindowsConsoleHelper::getKey());
#endif
#ifdef __linux__
    return static_cast<GameKey>(LinuxConsoleHelper::getKey());
#endif
}

void ConsoleHelper::useColor(ConsoleColor color) {
#ifdef __linux__
    const char * printColor = "";
#endif
#ifdef _WIN32
    int printColor = 0;
#endif
    switch (color) {
        case BG_BLACK: { printColor = BLACK_BACKGROUND; break; }
        case BG_RED: { printColor = RED_BACKGROUND; break; }
        case BG_GREEN: { printColor = GREEN_BACKGROUND; break; }
        case BG_YELLOW: { printColor = YELLOW_BACKGROUND; break; }
        case BG_BLUE: { printColor = BLUE_BACKGROUND; break; }
        case BG_MAGENTA: { printColor = MAGENTA_BACKGROUND; break; }
        case BG_CYAN: { printColor = CYAN_BACKGROUND; break; }
        case BG_WHITE: { printColor = WHITE_BACKGROUND; break; }
        case FG_BLACK: { printColor = BLACK_FOREGROUND; break; }
        case FG_RED: { printColor = RED_FOREGROUND; break; }
        case FG_GREEN: { printColor = GREEN_FOREGROUND; break; }
        case FG_YELLOW: { printColor = YELLOW_FOREGROUND; break; }
        case FG_BLUE: { printColor = BLUE_FOREGROUND; break; }
        case FG_MAGENTA: { printColor = MAGENTA_FOREGROUND; break; }
        case FG_CYAN: { printColor = CYAN_FOREGROUND; break; }
        case FG_WHITE: { printColor = WHITE_FOREGROUND; break; }
        case C_RESET: { printColor = COLOR_RESET; break; }
        case C_SELECTION: { printColor = SELECTION; break; }
    }
#ifdef __linux__
    printf("%s", printColor);
#endif
#ifdef _WIN32
    SetConsoleTextAttribute(WindowsConsoleHelper::getHandle(), printColor);
#endif
}

void ConsoleHelper::clearBelow() {
    ConsoleHelper::moveCursor(0, BOARD_HEIGHT);
    for (int i = 0; i < BOARD_WIDTH; ++i) ConsoleHelper::print(" ");
    fflush(stdout);
}

void ConsoleHelper::printWinBanner(const char *text, ConsoleColor color) {
    int length = strlen(text);
    int paddingX = (BOARD_WIDTH - (length + 2)) / 2;
    int paddingY = (BOARD_HEIGHT - 3) / 2;
    ConsoleHelper::moveCursor(paddingX, paddingY);
    ConsoleHelper::useColor(color);
    ConsoleHelper::print(TOP_LEFT_CORNER);
    for (int i = 0; i < length; ++i) ConsoleHelper::print(HORIZONTAL_BORDER);
    ConsoleHelper::print(TOP_RIGHT_CORNER);
    ConsoleHelper::useColor(C_RESET);
    ConsoleHelper::moveCursor(paddingX, paddingY + 1);
    ConsoleHelper::useColor(color);
    ConsoleHelper::print(VERTICAL_BORDER);
    ConsoleHelper::useColor(C_RESET);
    ConsoleHelper::print(text);
    ConsoleHelper::useColor(color);
    ConsoleHelper::print(VERTICAL_BORDER);
    ConsoleHelper::useColor(C_RESET);
    ConsoleHelper::moveCursor(paddingX, paddingY + 2);
    ConsoleHelper::useColor(color);
    ConsoleHelper::print(BOTTOM_LEFT_CORNER);
    for (int i = 0; i < length; ++i) ConsoleHelper::print(HORIZONTAL_BORDER);
    ConsoleHelper::print(BOTTOM_RIGHT_CORNER);
    ConsoleHelper::useColor(C_RESET);
}

int ConsoleHelper::select(const char * option1, const char * option2, int _selected) {
    int selected = _selected;
    bool fixed = false;
    int length = strlen(option1) + strlen(option2);
    if(length > BOARD_WIDTH) return -1;
    ConsoleHelper::clearBelow();

    auto printOption = [](const char * option, bool highlighted = false) {
        if(highlighted) ConsoleHelper::useColor(C_SELECTION);
        else ConsoleHelper::useColor(FG_BLACK);
        ConsoleHelper::print(option);
        ConsoleHelper::useColor(C_RESET);
    };

    auto printSelect = [&option1, &option2, &length, &printOption, &selected]() {
        ConsoleHelper::moveCursor(0, BOARD_HEIGHT);
        printOption(option1, selected == 0);
        for (int i = 0; i < BOARD_WIDTH - length; ++i) ConsoleHelper::print(" ");
        printOption(option2, selected == 1);
        fflush(stdout);
    };

    printSelect();
    do {
        GameKey key = ConsoleHelper::getKey();
        if(key == RIGHT && selected == 0) { selected++; printSelect(); }
        else if(key == LEFT && selected == 1) { selected--; printSelect(); }
        else if(key == ENTER) fixed = true;
    } while(!fixed);
    return selected;
}

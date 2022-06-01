#ifndef TICTACTOE_CONSOLEHELPER_H
#define TICTACTOE_CONSOLEHELPER_H

#ifdef _WIN32
#include "WindowsConsoleHelper.h"
#include "windows.h"
#endif
#ifdef __linux__
#include "LinuxConsoleHelper.h"
#define BACKGROUND_BLACK        "\x1b[40;1m"
#define BACKGROUND_RED          "\x1b[41;1m"
#define BACKGROUND_GREEN        "\x1b[42;1m"
#define BACKGROUND_YELLOW       "\x1b[43;1m"
#define BACKGROUND_BLUE         "\x1b[44;1m"
#define BACKGROUND_MAGENTA      "\x1b[45;1m"
#define BACKGROUND_CYAN         "\x1b[46;1m"
#define BACKGROUND_WHITE        "\x1b[47;1m"
#endif

#define TOP_LEFT_CORNER         "┏"
#define TOP_RIGHT_CORNER        "┓"
#define TOP_LEFT_CORNER         "┏"
#define TOP_RIGHT_CORNER        "┓"
#define BOTTOM_LEFT_CORNER      "┗"
#define BOTTOM_RIGHT_CORNER     "┛"
#define VERTICAL_BORDER         "┃"
#define HORIZONTAL_BORDER       "━"
#define TOP_CROSSING_BORDER     "┳"
#define BOTTOM_CROSSING_BORDER  "┻"
#define RIGHT_CROSSING_BORDER   "┫"
#define LEFT_CROSSING_BORDER    "┣"
#define CROSSING_BORDER         "╋"

#define COLOR_BLACK             "\x1b[30;1m"
#define COLOR_RED               "\x1b[31;1m"
#define COLOR_GREEN             "\x1b[32;1m"
#define COLOR_YELLOW            "\x1b[33;1m"
#define COLOR_BLUE              "\x1b[34;1m"
#define COLOR_MAGENTA           "\x1b[35;1m"
#define COLOR_CYAN              "\x1b[36;1m"
#define COLOR_WHITE             "\x1b[37;1m"
#define COLOR_RESET             "\x1b[0m"

enum GameKey {
    NONE = -1,
    UP = 0,
    DOWN = 1,
    RIGHT = 2,
    LEFT = 3,
    ENTER = 4,
    ESCAPE = 5,
};

class ConsoleHelper {
public:
    /**
     * Clear the terminal
     */

    static void clearTerminal();

    /**
     * Move the cursor to a given position
     * @param x column
     * @param y row
     */

    static void moveCursor(short int x, short int y);

    /**
     * Write chars to a given position of the terminal
     * @param x column
     * @param y row
     * @param characters characters
     */

    static void writeCharsAt(short int x, short int y, const char * characters);

    /**
     * Write characters to output [to keep track of the x-coordinate]
     * @param characters characters to print
     */

    static void print(const char * characters);

    /**
     * Draw an empty board
     */

    static void drawEmptyBoard();

    /**
     * Show the cursor in the terminal
     */

    static void showCursor();

    /**
     * Hide the cursor in the terminal
     */

    static void hideCursor();

    /**
     * Get the next game relevant key
     * @return next game relevant key
     */

    [[nodiscard]] static GameKey getKey();

    /**
     * Initialize the console helper
     */

    void initialize();
private:
    static inline unsigned int cursorY = 0;
};


#endif //TICTACTOE_CONSOLEHELPER_H

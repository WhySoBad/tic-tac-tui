#ifndef TICTACTOE_CONSOLEHELPER_H
#define TICTACTOE_CONSOLEHELPER_H

#ifdef _WIN32
#include "WindowsConsoleHelper.h"
#include "windows.h"
#endif
#ifdef __linux__
#include "LinuxConsoleHelper.h"
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
     * Draw an empty board
     * @param x x coordinate of the top left corner of the board
     * @param y y coordinate of the top left corner of the board
     */

    static void drawEmptyBoard(short int x, short int y);
private:
};


#endif //TICTACTOE_CONSOLEHELPER_H

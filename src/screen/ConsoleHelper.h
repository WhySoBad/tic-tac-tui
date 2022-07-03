#ifndef TICTACTOE_CONSOLEHELPER_H
#define TICTACTOE_CONSOLEHELPER_H

#ifdef _WIN32
#include "WindowsConsoleHelper.h"
#include "windows.h"
#define BLACK_BACKGROUND        BACKGROUND_INTENSITY
#define RED_BACKGROUND          BACKGROUND_INTENSITY | BACKGROUND_RED
#define GREEN_BACKGROUND        BACKGROUND_GREEN
#define YELLOW_BACKGROUND       BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN
#define BLUE_BACKGROUND         BACKGROUND_BLUE
#define MAGENTA_BACKGROUND      BACKGROUND_RED | BACKGROUND_BLUE
#define CYAN_BACKGROUND         BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE
#define WHITE_BACKGROUND        BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN
#define BLACK_FOREGROUND        FOREGROUND_INTENSITY
#define RED_FOREGROUND          FOREGROUND_INTENSITY | FOREGROUND_RED
#define GREEN_FOREGROUND        FOREGROUND_GREEN
#define YELLOW_FOREGROUND       FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define BLUE_FOREGROUND         FOREGROUND_BLUE
#define MAGENTA_FOREGROUND      FOREGROUND_RED | FOREGROUND_BLUE
#define CYAN_FOREGROUND         FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define WHITE_FOREGROUND        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define COLOR_RESET             0 | WHITE_FOREGROUND
#define SELECTION               WHITE_BACKGROUND | BLACK_FOREGROUND
#endif
#ifdef __linux__
#include "LinuxConsoleHelper.h"
#define BLACK_BACKGROUND        "\x1b[40;1m"
#define RED_BACKGROUND          "\x1b[41;1m"
#define GREEN_BACKGROUND        "\x1b[42;1m"
#define YELLOW_BACKGROUND       "\x1b[43;1m"
#define BLUE_BACKGROUND         "\x1b[44;1m"
#define MAGENTA_BACKGROUND      "\x1b[45;1m"
#define CYAN_BACKGROUND         "\x1b[46;1m"
#define WHITE_BACKGROUND        "\x1b[47;1m"
#define BLACK_FOREGROUND        "\x1b[30;1m"
#define RED_FOREGROUND          "\x1b[31;1m"
#define GREEN_FOREGROUND        "\x1b[32;1m"
#define YELLOW_FOREGROUND       "\x1b[33;1m"
#define BLUE_FOREGROUND         "\x1b[34;1m"
#define MAGENTA_FOREGROUND      "\x1b[35;1m"
#define CYAN_FOREGROUND         "\x1b[36;1m"
#define WHITE_FOREGROUND        "\x1b[37;1m"
#define COLOR_RESET             "\x1b[0m"
#define SELECTION               "\x1b[47;1m\x1b[30;1m"
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

enum ConsoleColor {
    BG_BLACK,
    BG_RED,
    BG_GREEN,
    BG_YELLOW,
    BG_BLUE,
    BG_MAGENTA,
    BG_CYAN,
    BG_WHITE,
    FG_BLACK,
    FG_RED,
    FG_GREEN,
    FG_YELLOW,
    FG_BLUE,
    FG_MAGENTA,
    FG_CYAN,
    FG_WHITE,
    C_RESET,
    C_SELECTION,
};

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
    static inline unsigned int cursorY = 0;
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
     * Clear the line below the board
     */

    static void clearBelow();

    /**
     * Print a banner with the winner's name
     */

    static void printWinBanner(const char * text, ConsoleColor color = FG_WHITE);

    /**
     * Create a select for two options
     * @param option1 option 1
     * @param option2 option 2
     * @param selected default selected item
     * @return 0 or 1
     */

    static int select(const char * option1, const char * option2, int selected = 0);

    /**
     * Show the cursor in the terminal
     */

    static void showCursor();

    /**
     * Hide the cursor in the terminal
     */

    static void hideCursor();

    /**
     * Activate a color for the console
     * @param color new color
     */

    static void useColor(ConsoleColor color);

    /**
     * Get the next game relevant key
     * @return next game relevant key
     */

    [[nodiscard]] static GameKey getKey();

    /**
     * Initialize the console helper
     */

    void initialize();
};


#endif //TICTACTOE_CONSOLEHELPER_H

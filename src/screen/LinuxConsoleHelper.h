#ifdef __linux__
#ifndef TICTACTOE_LINUXCONSOLEHELPER_H
#define TICTACTOE_LINUXCONSOLEHELPER_H

enum LinuxGameKey {
    K_NONE = -1,
    K_UP = 0,
    K_DOWN = 1,
    K_RIGHT = 2,
    K_LEFT = 3,
    K_ENTER = 4,
    K_ESCAPE = 5,
};

struct Position {
    short int x;
    short int y;
};

class LinuxConsoleHelper {
    static inline unsigned short startLine = 0;
public:
    /**
     * Get the current cursor position in the terminal
     * @return position of the cursor
     */

    [[nodiscard]] static Position getCursorPosition();

    /**
     * Get the start line of the terminal
     * @return start line of the terminal
     */

    [[nodiscard]] static unsigned short getStartLine();

    /**
     * Set the start line of the terminal
     * @param line new start line
     */

    static void setStartLine(unsigned short line);

    /**
     * Clean the console up before exiting
     */

    static void cleanup();

    /**
     * Get the next game relevant key
     * @return next game relevant key
     */

    [[nodiscard]] static LinuxGameKey getKey();

    /**
     * Initialize the LinuxConsoleHelper
     */

    static void initialize();
};


#endif //TICTACTOE_LINUXCONSOLEHELPER_H
#endif
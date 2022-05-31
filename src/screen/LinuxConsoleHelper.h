#ifdef __linux__
#ifndef TICTACTOE_LINUXCONSOLEHELPER_H
#define TICTACTOE_LINUXCONSOLEHELPER_H

struct Position {
    short int x;
    short int y;
};

class LinuxConsoleHelper {
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
     * Initialize the LinuxConsoleHelper
     */

    static void initialize();
private:
    static inline unsigned short startLine = 0;
};


#endif //TICTACTOE_LINUXCONSOLEHELPER_H
#endif
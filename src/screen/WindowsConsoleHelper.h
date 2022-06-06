#ifdef _WIN32
#ifndef TICTACTOE_WINDOWSCONSOLEHELPER_H
#define TICTACTOE_WINDOWSCONSOLEHELPER_H

#include "windows.h"

enum WinGameKey {
    W_NONE = -1,
    W_UP = 0,
    W_DOWN = 1,
    W_RIGHT = 2,
    W_LEFT = 3,
    W_ENTER = 4,
    W_ESCAPE = 5,
};

class WindowsConsoleHelper {
public:

    /**
     * Initialize the console helper
     */

    static void initialize();

    /**
     * Clean the console up
     */

    static void cleanup();

    /**
     * Get the console handle
     * @return current console handle
     */

    [[nodiscard]] static HANDLE getHandle();

    /**
     * Set a new console handle
     * @param handle new console handle
     */

    static void setHandle(HANDLE handle);

    /**
     * Get the start line of the terminal
     * @return start line of the terminal
     */

    [[nodiscard]] static unsigned short getStartLine();

    /**
    * Get the next game relevant key
    * @return next game relevant key
    */

    [[nodiscard]] static WinGameKey getKey();
private:
    static inline unsigned short startLine = 0;
    inline static HANDLE handle;
    inline static DWORD mode;
};


#endif //TICTACTOE_WINDOWSCONSOLEHELPER_H
#endif
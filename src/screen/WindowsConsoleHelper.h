#ifdef _WIN32
#ifndef TICTACTOE_WINDOWSCONSOLEHELPER_H
#define TICTACTOE_WINDOWSCONSOLEHELPER_H

#include "windows.h"

class WindowsConsoleHelper {
public:

    /**
     * Initialize the console helper
     */

    static void initialize();

    /**
     * Clean the console up
     */

    static void cleanUp();

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
private:
    inline static HANDLE handle;
    inline static DWORD mode;
};


#endif //TICTACTOE_WINDOWSCONSOLEHELPER_H
#endif
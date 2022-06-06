#include <cstring>
#include "game/Board.h"
#include "iostream"
#include "game/Game.h"
#include "screen/ConsoleHelper.h"
#include "string"

#ifdef _WIN32
#include "screen/WindowsConsoleHelper.h"
#include "windows.h"
#endif
#ifdef __linux__
#include "screen/LinuxConsoleHelper.h"
#include "csignal"
#include "sys/ioctl.h"
#endif

void handleSignal(int sig) {
    ConsoleHelper::moveCursor(0, BOARD_HEIGHT + 1);
    ConsoleHelper::useColor(C_RESET);
    ConsoleHelper::showCursor();
#ifdef __linux__
    LinuxConsoleHelper::cleanup();
#endif
#ifdef _WIN32
    WindowsConsoleHelper::cleanup();
#endif
    exit(sig);
}

int main() {
    signal(SIGINT, handleSignal); // sigint handler
    signal(SIGTERM, handleSignal); // sigterm handler
#ifdef _WIN32
    WindowsConsoleHelper::initialize(); // initialize windows console helper
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(WindowsConsoleHelper::getHandle(), &info);
    int columns = info.srWindow.Right - info.srWindow.Left + 1;
    int rows = info.srWindow.Bottom - info.srWindow.Top + 1;
        if(rows - WindowsConsoleHelper::getStartLine() < BOARD_HEIGHT + 1 && columns < BOARD_WIDTH) {
        fprintf(stderr, "The terminal is too small [Required width: %i; Required height: %i]\n", BOARD_WIDTH, BOARD_HEIGHT + 1);
        return 0;
    } else if(rows - WindowsConsoleHelper::getStartLine() < (BOARD_HEIGHT + 1)) {
        fprintf(stderr, "The terminal is too small [Required height: %i]\n", BOARD_HEIGHT + 1);
        return 0;
    } else if(columns < BOARD_WIDTH) {
        fprintf(stderr, "The terminal is too small [Required width: %i]\n", BOARD_WIDTH);
        return 0;
    }
#endif
#ifdef __linux__
    LinuxConsoleHelper::initialize(); // initialize linux console helper
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    if(size.ws_row - LinuxConsoleHelper::getStartLine() < BOARD_HEIGHT + 1 && size.ws_col < BOARD_WIDTH) {
        fprintf(stderr, "The terminal is too small [Required width: %i; Required height: %i]\n", BOARD_WIDTH, BOARD_HEIGHT + 1);
        return 0;
    } else if(size.ws_row - LinuxConsoleHelper::getStartLine() < (BOARD_HEIGHT + 1)) {
        fprintf(stderr, "The terminal is too small [Required height: %i]\n", BOARD_HEIGHT + 1);
        return 0;
    } else if(size.ws_col < BOARD_WIDTH) {
        fprintf(stderr, "The terminal is too small [Required width: %i]\n", BOARD_WIDTH);
        return 0;
    }
#endif

    ConsoleHelper::hideCursor();
    Game game = Game();
    game.start();
    while(game.shouldRestart()) { game.start(); }
    ConsoleHelper::moveCursor(0, BOARD_HEIGHT - 1); // move the cursor at the bottom
    ConsoleHelper::showCursor();
    fflush(stdout);
    return 0;
}

// ┏━0━━━━━┳━1━━━━━┳━2━━━━━┓
// ┃ ||||| ┃ ##### ┃ ##### ┃
// ┃ ||||| ┃ ##### ┃ ##### ┃
// ┣━3━━━━━╋━4━━━━━╋━5━━━━━┫
// ┃ ||||| ┃       ┃ ##### ┃
// ┃ ||||| ┃       ┃ ##### ┃
// ┣━6━━━━━╋━7━━━━━╋━8━━━━━┫
// ┃ ||||| ┃ ##### ┃       ┃
// ┃ ||||| ┃ ##### ┃       ┃
// ┗━━━━━━━┻━━━━━━━┻━━━━━━━┛

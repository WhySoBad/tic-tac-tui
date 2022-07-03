#include "game/Board.h"
#include "game/Game.h"
#include "screen/ConsoleHelper.h"
#include "string"

// TODO: Linux clear input buffer after computer turn

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
    ConsoleHelper::clearBelow();
    ConsoleHelper::moveCursor(0, BOARD_HEIGHT - 1);
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
    if(columns < BOARD_WIDTH) {
        fprintf(stderr, "The terminal is too small [Required width: %i]\n", BOARD_WIDTH);
        return 0;
    }
    if(WindowsConsoleHelper::getStartLine() + BOARD_HEIGHT > rows) {
        unsigned short move = WindowsConsoleHelper::getStartLine() + BOARD_HEIGHT - rows + 1;
        SMALL_RECT rect;
        rect.Top =- move;
        rect.Bottom =- move;
        rect.Left = 0;
        rect.Right = 0;
        SetConsoleWindowInfo(WindowsConsoleHelper::getHandle(), FALSE, &rect);
        WindowsConsoleHelper::setStartLine(WindowsConsoleHelper::getStartLine() - move);
        for (int i = 0; i < BOARD_HEIGHT; ++i) ConsoleHelper::print("\n");
    }
    fflush(stdout);
#endif
#ifdef __linux__
    LinuxConsoleHelper::initialize(); // initialize linux console helper
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    if(size.ws_col < BOARD_WIDTH) {
        fprintf(stderr, "The terminal is too small [Required width: %i]\n", BOARD_WIDTH);
        return 0;
    }
    if(LinuxConsoleHelper::getCursorPosition().y + BOARD_HEIGHT > size.ws_row) {
        unsigned short move = LinuxConsoleHelper::getCursorPosition().y + BOARD_HEIGHT - size.ws_row + 1;
        printf("\x1b[%iS", move);
        LinuxConsoleHelper::setStartLine(LinuxConsoleHelper::getCursorPosition().y - move);
    }
    fflush(stdout);
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

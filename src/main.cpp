#include "game/Board.h"
#include "cstdio"
#include "iostream"
#include "game/Game.h"
#include "screen/ConsoleHelper.h"

#ifdef _WIN32
#include "screen/WindowsConsoleHelper.h"
#include "windows.h"
#endif
#ifdef __linux__
#include "screen/LinuxConsoleHelper.h"
#endif

int main() {
#ifdef _WIN32
    WindowsConsoleHelper::initialize(); // initialize windows console helper
#endif
#ifdef __linux__
    LinuxConsoleHelper::initialize(); // initialize linux console helper
#endif
    Board board = Board();
    board.drawBoard();
    while(1) {} // keep process artificially alive
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

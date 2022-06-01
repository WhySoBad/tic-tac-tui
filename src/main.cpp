#include "game/Board.h"
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
    ConsoleHelper::hideCursor();
    Game game = Game(SINGLEPLAYER);
    game.start();
    game.getBoard()->selectField(5, game.getActive()->getColor());
    while(game.isRunning()) {
        int selected = game.getBoard()->getSelected();
        GameKey current = ConsoleHelper::getKey();
        if(selected < 0) {
            game.getBoard()->selectField(0, game.getActive()->getColor());
            continue;
        } else {
            switch (current) {
                case UP: { if((int) (selected / ROWS > 0)) game.getBoard()->selectField(selected - COLUMNS,game.getActive()->getColor()); break; };
                case DOWN: { if((int) (selected / ROWS < (ROWS - 1))) game.getBoard()->selectField(selected + COLUMNS,game.getActive()->getColor()); break; };
                case LEFT: { if(selected % COLUMNS > 0) game.getBoard()->selectField(selected - 1,game.getActive()->getColor()); break; }
                case RIGHT: { if(selected % COLUMNS < (COLUMNS - 1)) game.getBoard()->selectField(selected + 1,game.getActive()->getColor()); break; };
                case ENTER: { if(selected >= 0) game.getBoard()->confirmSelection(game.getActive()); break; };
                case ESCAPE: { game.stop(false); break; }
            }
        }
        fflush(stdout);
    } // keep process artificially alive
    ConsoleHelper::moveCursor(0, BOARD_HEIGHT + 2); // move the cursor at the bottom
    ConsoleHelper::showCursor();
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

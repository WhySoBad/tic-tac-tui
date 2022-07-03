#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H


#include "Board.h"
#include "Player.h"

enum Gamemode {
    SINGLEPLAYER = 0,
    LOCAL_MULTIPLAYER = 1,
};

class Game {
    Gamemode mode;
    Board *board;
    Player *player1;
    Player *player2;
    Player *active;
    bool running = false;
    bool restart = false;

    /**
     * Reset the game
     */

    void reset();

public:
    void start();

    /**
     * Get the mode the game is running on
     * @return mode the game is running on
     */

    [[nodiscard]] Gamemode getMode() const;

    /**
     * Get the board instance
     * @return board instance
     */

    [[nodiscard]] Board *getBoard() const;

    /**
     * Get the first player
     * @return first player
     */

    [[nodiscard]] Player *getFirstPlayer() const;

    /**
     * Get the second player
     * @return second player
     */

    [[nodiscard]] Player *getSecondPlayer() const;

    /**
     * Get the active player
     * @return active player
     */

    [[nodiscard]] Player *getActive() const;

    /**
     * Get whether the game is running or not
     * @return boolean whether the game is running
     */

    [[nodiscard]] bool isRunning() const;

    /**
     * Get whether a new round should be started after the game was stopped
     * @return boolean whether a new round should be started after the game was stopped
     */

    bool shouldRestart() const;

    Game() = default;
};


#endif //TICTACTOE_GAME_H

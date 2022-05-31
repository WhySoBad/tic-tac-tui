#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H


#include "Board.h"
#include "Player.h"

enum Gamemode {
    LOCAL_MULTIPLAYER = 0,
    SINGLEPLAYER = 1,
};

class Game {
public:
    void start();

    Game(Gamemode gamemode = SINGLEPLAYER);
private:
    Gamemode mode;
    Board* board;
    Player* player1;
    Player* player2;
    Player* active = nullptr;
};


#endif //TICTACTOE_GAME_H

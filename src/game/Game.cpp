#include "Game.h"
#include "chrono"
#include "iostream"

Game::Game(Gamemode gamemode) {
    mode = gamemode;
}

void Game::start() {
    auto now = std::chrono::high_resolution_clock::now();
    unsigned short int starter = static_cast<unsigned short int>(std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count()) % 2;
    active = starter == 0 ? player1 : player2;
}

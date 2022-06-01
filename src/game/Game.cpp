#include "Game.h"
#include "chrono"
#include "iostream"

Game::Game(Gamemode gamemode) {
    mode = gamemode;
    board = new Board();
    player1 = new Player(PLAYER_1, COLOR_BLUE, "#", false);
    player2 = new Player(PLAYER_2, COLOR_RED, "*", true);
}

void Game::start() {
    auto now = std::chrono::high_resolution_clock::now();
    unsigned short int starter = static_cast<unsigned short int>(std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count()) % 2;
    active = starter == 0 ? player1 : player2;
    board->drawBoard();
    running = true;
}

Gamemode Game::getMode() const {
    return mode;
}

Board *Game::getBoard() const {
    return board;
}

Player *Game::getFirstPlayer() const {
    return player1;
}

Player *Game::getSecondPlayer() const {
    return player2;
}

Player *Game::getActive() const {
    return active;
}

bool Game::isRunning() const {
    return running;
}

void Game::stop(bool restart) {
    this->restart = restart;
    running = false;
}

bool Game::shouldRestart() const {
    return restart;
}

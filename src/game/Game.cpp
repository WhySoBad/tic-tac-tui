#include "Game.h"
#include "iostream"
#include "random"
#include "Computer.h"

#ifdef __linux__
#include "termios.h"
#include "unistd.h"
#endif

inline std::mt19937 &generator() {
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

void Game::start() {
    reset();
    ConsoleHelper::clearBelow();
    board->drawBoard();
    running = true;
    int turns = 1;
    do {
        active = turns % 2 == 1 ? player1 : player2;
        board->selectField(board->getSelected(), active->getColor());

        if(auto *computer = dynamic_cast<Computer*>(active)) {
            computer->pickField();
            if(board->getWinner() != UNOCCUPIED || board->isBoardFull()) {
                board->selectField(-1);
                running = false;
            }
            fflush(stdout);
#ifdef __linux__
            tcflush(STDIN_FILENO,TCIFLUSH);
#endif
        } else {
            bool fixed = false;
            do {
                GameKey key = ConsoleHelper::getKey();
                if(key == ESCAPE) { running = false; fixed = true; continue; }
                int selected = board->getSelected();
                if(selected < 0) { board->selectField(0, active->getColor()); fflush(stdout); continue; }
                switch(key) {
                    case UP: { if((int) (selected / ROWS > 0)) board->selectField(selected - COLUMNS, active->getColor()); break; };
                    case DOWN: { if((int) (selected / ROWS < (ROWS - 1))) board->selectField(selected + COLUMNS, active->getColor()); break; };
                    case LEFT: { if(selected % COLUMNS > 0) board->selectField(selected - 1, active->getColor()); break; }
                    case RIGHT: { if(selected % COLUMNS < (COLUMNS - 1)) board->selectField(selected + 1, active->getColor()); break; };
                    case ENTER: { if(selected >= 0 && board->getFieldOwner(selected) == UNOCCUPIED) board->confirmSelection(active); fixed = true; break; };
                }
                if(board->getWinner() != UNOCCUPIED) {
                    fixed = true;
                    board->selectField(-1);
                    running = false;
                } else if(board->isBoardFull()) {
                    fixed = true;
                    running = false;
                    board->selectField(-1);
                }
                fflush(stdout);
            } while(!fixed);
        }
        turns++;
    } while(running);
    if(board->getWinner() != UNOCCUPIED || board->isBoardFull()) {
        if(board->getWinner() != UNOCCUPIED) {
            if(board->getWinner() == player1->getId()) ConsoleHelper::printWinBanner(" Player 1 won! ", player1->getColor());
            else if(auto *computer = dynamic_cast<Computer*>(player2)) ConsoleHelper::printWinBanner(" Computer won! ", player2->getColor());
            else ConsoleHelper::printWinBanner(" Player 2 won! ", player2->getColor());
        } else ConsoleHelper::printWinBanner(" It's a draw! ");
        restart = ConsoleHelper::select(" PLAY AGAIN ", " EXIT ") == 0;
        ConsoleHelper::clearBelow();
    }
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

bool Game::shouldRestart() const {
    return restart;
}

void Game::reset() {
    restart = false;
    running = false;
    ConsoleHelper::drawEmptyBoard();
    board = new Board();

    mode = static_cast<Gamemode>(ConsoleHelper::select(" ONE PLAYER ", " TWO PLAYERS "));

    std::uniform_int_distribution<int> distribution(FG_RED, FG_CYAN);
    int color = distribution(generator());
    player1 = new Player(PLAYER_1, static_cast<ConsoleColor>(color), "#", false);
    color = distribution(generator());
    while(color == player1->getColor()) color = distribution(generator());

    if(mode == LOCAL_MULTIPLAYER) {
        player2 = new Player(PLAYER_2, static_cast<ConsoleColor>(color), "*", true);
    } else {
        player2 = new Computer(board, PLAYER_2, static_cast<ConsoleColor>(color), "*", true);
    }
}
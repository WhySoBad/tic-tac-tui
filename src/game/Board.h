#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H

#include "array"

#define PLAYER_1        0
#define PLAYER_2        1
#define UNOCCUPIED      2

#define ROWS            3
#define COLUMNS         3

#define CELL_HEIGHT     2
#define CELL_WIDTH      7
#define CELL_CONTENT    5

#define BOARD_HEIGHT    ROWS + 1 + CELL_HEIGHT * ROWS
#define BOARD_WIDTH     COLUMNS + 1 + CELL_WIDTH * COLUMNS

class Board {
public:
    /**
     * Get all fields
     * @return array with all fields
     */

    [[nodiscard]] std::array<unsigned char, ROWS * COLUMNS> getFields();

    /**
     * Get whether a field is empty
     * @param field field to be checked
     * @return boolean whether the field is empty
     */

    [[nodiscard]] bool isFieldEmpty(unsigned char field);

    /**
     * Occupy a field if it isn't occupied already
     * @param field field to be occupied
     * @param player player to occupy the field
     */

    void occupyField(unsigned char field, bool player);

    /**
     * Get the owner of a given field
     * @param field field to get the owner of
     * @return owner of the field
     */

    [[nodiscard]] unsigned char getFieldOwner(unsigned char field);

    /**
     * Get the winner of the board
     * @return winner of the board [2 = no winner]
     */

    [[nodiscard]] unsigned char getWinner() const;

    /**
     * Draw the board at a given position [top left coordinate]
     */

    void drawBoard();

    [[nodiscard]] unsigned short getX() const;

    [[nodiscard]] unsigned short getY() const;

    void setX(unsigned short x);

    void setY(unsigned short y);

    Board();

private:
    std::array<unsigned char, ROWS * COLUMNS> fields{};
    unsigned short int x = 0;
    unsigned short int y = 0;
    unsigned char winner = 2; // no winner

    /**
     * Check whether the game has a winner
     * @return id of the winner [2 = no winner]
     */

    [[nodiscard]] unsigned char checkForWinner();
};


#endif //TICTACTOE_BOARD_H

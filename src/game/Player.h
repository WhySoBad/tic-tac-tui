
#ifndef TIC_TAC_TUI_PLAYER_H
#define TIC_TAC_TUI_PLAYER_H


#include "../screen/ConsoleHelper.h"

class Player {
    unsigned char id;
    ConsoleColor color;
    const char * character;
    bool outlined;
public:

    /**
     * Get the color of the player
     * @return color of the player
     */

    [[nodiscard]] ConsoleColor getColor() const;

    /**
     * Get the character of the player
     * @return character of the player
     */

    [[nodiscard]] const char *getCharacter() const;

    /**
     * Get whether the player's highlights should be outlined
     * @return boolean whether the player's highlights should be outlined
     */

    [[nodiscard]] bool isOutlined() const;

    /**
     * Get the id of the player
     * @return id of the player
     */

    [[nodiscard]] unsigned char getId() const;

    Player(unsigned char id, ConsoleColor color, const char * character, bool outlined);
    virtual ~Player() = default;
};


#endif //TIC_TAC_TUI_PLAYER_H

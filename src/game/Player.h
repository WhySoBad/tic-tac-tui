
#ifndef TIC_TAC_TUI_PLAYER_H
#define TIC_TAC_TUI_PLAYER_H


#include "../screen/ConsoleHelper.h"

class Player {
public:

    [[nodiscard]] ConsoleColor getColor() const;

    [[nodiscard]] const char *getCharacter() const;

    [[nodiscard]] bool isOutlined() const;

    [[nodiscard]] unsigned char getId() const;

    Player(unsigned char id, ConsoleColor color, const char * character, bool outlined);
    virtual ~Player() = default;
private:
    unsigned char id;
    ConsoleColor color;
    const char * character;
    bool outlined;
};


#endif //TIC_TAC_TUI_PLAYER_H

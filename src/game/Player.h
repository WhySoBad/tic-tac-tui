
#ifndef TIC_TAC_TUI_PLAYER_H
#define TIC_TAC_TUI_PLAYER_H


class Player {
public:

    [[nodiscard]] const char *getColor() const;

    [[nodiscard]] const char *getCharacter() const;

    [[nodiscard]] bool isOutlined() const;

    [[nodiscard]] unsigned char getId() const;

    Player(unsigned char id, const char * color, const char * character, bool outlined);
private:
    unsigned char id;
    const char * color;
    const char * character;
    bool outlined;
};


#endif //TIC_TAC_TUI_PLAYER_H

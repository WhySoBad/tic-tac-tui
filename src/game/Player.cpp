#include "Player.h"

ConsoleColor Player::getColor() const {
    return color;
}

const char *Player::getCharacter() const {
    return character;
}

bool Player::isOutlined() const {
    return outlined;
}


unsigned char Player::getId() const {
    return id;
}

Player::Player(unsigned char id, ConsoleColor color, const char *character, bool outlined) {
    this->id = id;
    this->color = color;
    this->character = character;
    this->outlined = outlined;
}


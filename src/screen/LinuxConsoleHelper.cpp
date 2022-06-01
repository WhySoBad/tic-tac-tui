#ifdef __linux__
#include "iostream"
#include "csignal"
#include "LinuxConsoleHelper.h"
#include "termios.h"
#include "cstdio"

Position LinuxConsoleHelper::getCursorPosition() {
    char buf[30]={0};
    int ret, i, pow;
    char ch;

    short int y = 0, x = 0;

    struct termios term{}, restore{};

    tcgetattr(0, &term);
    tcgetattr(0, &restore);
    term.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(0, TCSANOW, &term);

    write(1, "\033[6n", 4);

    for( i = 0, ch = 0; ch != 'R'; i++ )
    {
        ret = read(0, &ch, 1);
        if (!ret) {
            tcsetattr(0, TCSANOW, &restore);
            fprintf(stderr, "getpos: error reading response!\n");
            return {0, 0};
        }
        buf[i] = ch;
    }

    if (i >= 2) {
        for(i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10) x = x + (buf[i] - '0') * pow;
        for(i-- , pow = 1; buf[i] != '['; i--, pow *= 10) y = y + (buf[i] - '0') * pow;
    }

    tcsetattr(0, TCSANOW, &restore);
    return {static_cast<short>(x - 1), static_cast<short>(y - 1)};
}

unsigned short LinuxConsoleHelper::getStartLine() {
    return startLine;
}

void LinuxConsoleHelper::initialize() {
    startLine = LinuxConsoleHelper::getCursorPosition().y;
}

LinuxGameKey LinuxConsoleHelper::getKey() {
    struct termios term = {0};
    if(tcgetattr(0, &term) < 0) fprintf(stderr, "tcgetattr: error whilst getting attribute\n");
    term.c_lflag &= ~ICANON; // disable canonical input
    term.c_lflag &= ~ECHO; // disable echo
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &term) < 0) fprintf(stderr, "tcsetattr: error whilst setting ICANON flag\n");
    LinuxGameKey key = K_NONE;
    do {
        char buffer[3] = {0, 0, 0};
        if(read(0, &buffer, 3) < 0) fprintf(stderr, "read: failed to read three bytes");
        if(buffer[0] == 27 && buffer[1] == 91) {
            if(buffer[2] == 65) key = K_UP;
            else if(buffer[2] == 66) key = K_DOWN;
            else if(buffer[2] == 67) key = K_RIGHT;
            else if(buffer[2] == 68) key = K_LEFT;
        } else if(buffer[0] == 27 && !buffer[1] && !buffer[2]) key = K_ESCAPE;
        else if(buffer[0] == 10 && !buffer[1] && !buffer[2]) key = K_ENTER;
    } while(key == K_NONE);
    term.c_lflag |= ICANON;
    term.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &term) < 0) fprintf(stderr, "tcsetattr: error whilst resetting ICANON flag\n");
    return key;
}
#endif

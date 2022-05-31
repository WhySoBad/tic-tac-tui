#ifdef __linux__
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
        for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10) x = x + ( buf[i] - '0' ) * pow;
        for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10) y = y + ( buf[i] - '0' ) * pow;
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
#endif

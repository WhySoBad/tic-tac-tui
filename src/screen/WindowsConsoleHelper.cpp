#ifdef _WIN32

#include "WindowsConsoleHelper.h"
#include "iostream"

HANDLE WindowsConsoleHelper::getHandle() {
    return handle;
}

void WindowsConsoleHelper::setHandle(HANDLE newHandle) {
    handle = newHandle;
}

void WindowsConsoleHelper::initialize() {
    SetConsoleOutputCP(CP_UTF8);
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD currentMode = 0;
    if(!GetConsoleMode(handle, &currentMode)) {
        fprintf(stderr, "Unable to get current console mode");
        return;
    }
    mode = currentMode;
    currentMode |= ENABLE_PROCESSED_INPUT | ENABLE_PROCESSED_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN | ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(handle, currentMode)) {
        fprintf(stderr, "Unable to update current console mode");
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO info;
    if(GetConsoleScreenBufferInfo(handle, &info)) {
        startLine = info.dwCursorPosition.Y;
    } else startLine = 0;
}

void WindowsConsoleHelper::cleanup() {
    if(!SetConsoleMode(handle, mode)) {
        fprintf(stderr, "Failed to restore initial console mode");
    }
}

WinGameKey WindowsConsoleHelper::getKey() {
    WinGameKey key = W_NONE;
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    DWORD currentMode = 0;

    if(!GetConsoleMode(handle, &currentMode)) {
        fprintf(stderr, "Unable to get current console mode");
        return W_NONE;
    }
    currentMode = ENABLE_WINDOW_INPUT;

    if(!SetConsoleMode(handle, currentMode)) {
        fprintf(stderr, "Unable to update current console mode");
        return W_NONE;
    }

    do {
        INPUT_RECORD buffer[1];
        DWORD read;
        if(!ReadConsoleInput(input, buffer, 1, &read)) fprintf(stderr, "ReadConsoleInput: Unable to read console input [%i]\n", GetLastError());
        for (int i = 0; i < read; ++i) {
            if(buffer[i].EventType != KEY_EVENT || !buffer[i].Event.KeyEvent.bKeyDown) continue;
            KEY_EVENT_RECORD current = buffer[i].Event.KeyEvent;
            switch (current.wVirtualKeyCode) {
                case VK_LEFT: { key = W_LEFT; break; };
                case VK_RIGHT: { key = W_RIGHT; break; };
                case VK_UP: { key = W_UP; break; };
                case VK_DOWN: { key = W_DOWN; break; };
                case VK_ESCAPE: { key = W_ESCAPE; break; };
                case VK_RETURN: { key = W_ENTER; break; };
            }
        }
    } while(key == W_NONE);
    return key;
}

unsigned short WindowsConsoleHelper::getStartLine() {
    return startLine;
}

void WindowsConsoleHelper::setStartLine(unsigned short line) {
    startLine = line;
}


#endif


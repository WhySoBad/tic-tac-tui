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
}

void WindowsConsoleHelper::cleanUp() {
    if(!SetConsoleMode(handle, mode)) {
        fprintf(stderr, "Failed to restore initial console mode");
    }
}

#endif
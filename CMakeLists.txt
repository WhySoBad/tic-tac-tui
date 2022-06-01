cmake_minimum_required(VERSION 3.22)
SET(PROJECT_NAME tic-tac-tui)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(${PROJECT_NAME} src/main.cpp src/game/Board.cpp src/game/Board.h src/game/Game.cpp src/game/Game.h src/screen/WindowsConsoleHelper.cpp src/screen/WindowsConsoleHelper.h src/screen/ConsoleHelper.cpp src/screen/ConsoleHelper.h src/screen/LinuxConsoleHelper.cpp src/screen/LinuxConsoleHelper.h src/game/Player.cpp src/game/Player.h)

IF(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
ENDIF()
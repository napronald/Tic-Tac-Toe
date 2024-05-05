#ifndef GAME_FUNCTION_H
#define GAME_FUNCTION_H

#include "GameState.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;

void startTimer(high_resolution_clock::time_point &start) {
    start = high_resolution_clock::now();
}

int getElapsedTime(high_resolution_clock::time_point start) {
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    return duration.count();
}

void printMenu() {
    std::cout << "Choose your game mode:\n";
    std::cout << "1. Play against another human\n";
    std::cout << "2. Play against a simple computer\n";
    std::cout << "3. Play against a hard computer\n";
    std::cout << "4. Exit the game\n";  //
    std::cout << "Select your option: ";
}

void printGameState(const GameState& state) {
    const char* greenStart = "\033[32m";
    const char* colorEnd = "\033[0m";

    int winType = 0;
    int winRowOrCol = -1;

    for (int i = 0; i < state.size; i++) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < state.size; j++) {
            if (state.grid[i][j] != state.grid[i][0]) {
                rowWin = false;
            }
            if (state.grid[j][i] != state.grid[0][i]) {
                colWin = false;
            }
        }
        if (rowWin && state.grid[i][0] != -1) {
            winType = 1;
            winRowOrCol = i;
            break;
        }
        if (colWin && state.grid[0][i] != -1) {
            winType = 2;
            winRowOrCol = i;
            break;
        }
    }

    bool mainDiagonalWin = true;
    bool secondaryDiagonalWin = true;
    for (int i = 0; i < state.size; i++) {
        if (state.grid[i][i] != state.grid[0][0]) {
            mainDiagonalWin = false;
        }
        if (state.grid[i][state.size - 1 - i] != state.grid[0][state.size - 1]) {
            secondaryDiagonalWin = false;
        }
    }
    if (mainDiagonalWin && state.grid[0][0] != -1) {
        winType = 3;
    } else if (secondaryDiagonalWin && state.grid[0][state.size - 1] != -1) {
        winType = 4;
    }

    std::cout << "   ";
    for (int j = 0; j < state.size; j++) {
        std::cout << " " << j << "  ";
    }
    std::cout << std::endl << "   ";
    for (int j = 0; j < state.size; j++) {
        std::cout << "--- ";
    }
    std::cout << std::endl;

    for (int i = 0; i < state.size; i++) {
        std::cout << i << " ";
        for (int j = 0; j < state.size; j++) {
            std::cout << "| ";
            if (state.grid[i][j] != -1) {
                char playerMark = (state.grid[i][j] == 1) ? 'O' : 'X';
                bool colorCell = false;
                switch (winType) {
                    case 1:
                        colorCell = (i == winRowOrCol);
                        break;
                    case 2:
                        colorCell = (j == winRowOrCol);
                        break;
                    case 3:
                        colorCell = (i == j);
                        break;
                    case 4:
                        colorCell = (i == state.size - 1 - j);
                        break;
                }
                if (colorCell) {
                    std::cout << greenStart << playerMark << colorEnd << " ";
                } else {
                    std::cout << playerMark << " ";
                }
            } else {
                std::cout << "  ";
            }
            if (j == state.size - 1) std::cout << "|";
        }
        std::cout << std::endl << "   ";
        for (int j = 0; j < state.size; j++) {
            std::cout << "--- ";
        }
        std::cout << std::endl;
    }
}

Vec validMove(const GameState& game) {
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                return Vec(i, j);
            }
        }
    }
    return Vec(-1, -1);
}

bool isValidStartPlayer(char c) {
    return c == 'x' || c == 'o';
}

#endif
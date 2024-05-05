#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "GameState.h"

bool anyMovesLeft(GameState game){
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                return true;
            }
        }
    }
    return false;
}

int minmax(GameState game, int depth, bool Botsturn){
    if(game.hasWon(1)){
        return 100-depth;
    } 
    if(game.hasWon(0)){
        return -100+depth;
    }
    if(!anyMovesLeft(game)){
        return 0;
    }
    int bestValue = (Botsturn) ? -999 : 999;

    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                game.play(i, j);
                int moveValue = minmax(game, depth + 1, !Botsturn);
                game.unPlay(i, j);
                bestValue = (Botsturn) ? std::max(bestValue, moveValue) : std::min(bestValue, moveValue);
            }
        }
    }
    return bestValue;
}

Vec findBestMove(GameState game){
    Vec bestMove(-1, -1);
    int bestMoveValue = -999;
    GameState gameCopy = game;

    for (int i = 0; i < gameCopy.size; i++) {
        for (int j = 0; j < gameCopy.size; j++) {
            if (gameCopy.grid[i][j] == -1) {
                gameCopy.play(i, j);
                int moveValue = minmax(gameCopy, 0, false);
                gameCopy.unPlay(i, j);
                if (moveValue > bestMoveValue) {
                    bestMove.set(i, j);
                    bestMoveValue = moveValue;
                }
            }
        }
    }
    return bestMove;
}

#endif
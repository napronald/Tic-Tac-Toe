#include <iostream>

#include "MinMax.h"
#include "GameFunction.h"

using namespace std;

int main() {
    int boardSize, choice;
    cout << "Welcome to Tic-Tac-Toe\n";
    do {
        printMenu();
        cin >> choice;

        if (choice == 4) {
            cout << "Exiting the game. Thank you for playing!\n";
            break; 
        }

        if (choice < 1 || choice > 4) {
            cout << "Invalid option. Please enter a valid choice (1-4).\n";
            continue; 
        }

        cout << "Enter the size of the game board (3-9): ";
        cin >> boardSize;
        while (cin.fail() || boardSize < 3 || boardSize > 9) {
            cout << "Invalid input. Please enter a valid size (3-9): ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> boardSize;
        }

        char firstPlayer;
        int moveTimeLimit;

        cout << "Do you want to be Player X or O? (Enter 'X' or 'O'): ";
        cin >> firstPlayer;
        firstPlayer = tolower(firstPlayer);
        while (!isValidStartPlayer(firstPlayer)) {
            cout << "Invalid input. Please enter 'X' or 'O'.\n";
            cin >> firstPlayer;
            firstPlayer = tolower(firstPlayer);
        }

        cout << "Enter time limit for each move in seconds (0 for no limit): ";
        cin >> moveTimeLimit;
        while (cin.fail() || moveTimeLimit < 0) {
            cout << "Invalid input. Please enter a non-negative number.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> moveTimeLimit;
        }
        moveTimeLimit *= 1000;

        GameState game(boardSize);
        game.currentTurn = (firstPlayer == 'o');

        int totalTimeX = 0;
        int totalTimeO = 0;

        while (!game.done) {
            cout << game << endl;

            Vec move;
            high_resolution_clock::time_point start;
            startTimer(start);

            if (choice == 1) {
                cout << "Enter row and column for " << (game.currentTurn ? "Player O" : "Player X") << ": ";
                cin >> move.x >> move.y;
            } else if (choice == 2) {
                if (!game.currentTurn) {
                    cout << "Enter row and column for Player X: ";
                    cin >> move.x >> move.y;
                } else {
                    move = validMove(game);
                    cout << "Computer plays " << move << endl;
                }
            } else if (choice == 3) {
                if (!game.currentTurn) {
                    cout << "Enter row and column for Player X: ";
                    cin >> move.x >> move.y;
                } else {
                    move = findBestMove(game);
                    cout << "Computer plays " << move << endl;
                }
            }

            int elapsedTime = getElapsedTime(start);
            cout << "Move took " << elapsedTime / 1000.0 << " seconds\n";
            if (moveTimeLimit > 0 && elapsedTime > moveTimeLimit) {
                cout << "Move time exceeded! Limit was " << moveTimeLimit / 1000 << " seconds. Move and turn skipped, changing to next player's turn.\n";
                if (game.currentTurn == 0) {
                    totalTimeX += elapsedTime;
                } else {
                    totalTimeO += elapsedTime;
                }
                game.currentTurn = !game.currentTurn;
                continue;
            }

            if (game.play(move.x, move.y)) {
                if (game.currentTurn == 0) {
                    totalTimeX += elapsedTime;
                } else {
                    totalTimeO += elapsedTime;
                }
            } else {
                cout << "Invalid move, try again.\n";
            }

            if (game.done) {
                printGameState(game);
                cout << "Game Over!\n";
                cout << "Total time for X: " << totalTimeX / 1000.0 << " seconds\n";
                cout << "Total time for O: " << totalTimeO / 1000.0 << " seconds\n";
                if (game.hasWon(0)) cout << "Player X wins!\n";
                else if (game.hasWon(1)) cout << "Player O wins!\n";
                else cout << "It's a draw!\n";
            }
        }
    } while (true);

    return 0;
}
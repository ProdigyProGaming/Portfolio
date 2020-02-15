//
// Created by Arron on 21/12/2019.
//

#include "Connect4.h"
#include <iostream>
#include "CommonFunctions.h"

using namespace std;

char board[8][8]{};
int winStatus;
bool checkWin() {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (i > 3) {
                if (board[i][j] == board[i-1][j] && board[i-1][j] == board[i-2][j] && board[i-2][j] == board[i-3][j] && (board[i][j] == 'X' || board[i][j] == 'O')) {
                    winStatus = board[i][j] == 'X' ? 3 : 2;
                    return true;
                }
            }

            //check left of current
            if (j > 2) {
                if (board[i][j] == board[i][j-1] && board[i][j-1] == board[i][j-2] && board[i][j-2] == board[i][j-3] && (board[i][j] == 'X' || board[i][j] == 'O')) {
                    winStatus = board[i][j] == 'X' ? 3 : 2;
                    return true;
                }
                else if (board[i][j] == board[i-1][j-1] && board[i-1][j-1] == board[i-2][j-2] && board[i-2][j-2] == board[i-3][j-3] && (board[i][j] == 'X' || board[i][j] == 'O')) {
                    winStatus = board[i][j] == 'X' ? 3 : 2;
                    return true;
                }
            }
            //check right of current
            if (j < 5) {
                if (board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2] && board[i][j+2] == board[i][j+3] && (board[i][j] == 'X' || board[i][j] == 'O')) {
                    winStatus = board[i][j] == 'X' ? 3 : 2;
                    return true;
                }
                else if (board[i][j] == board[i-1][j+1] && board[i-1][j+1] == board[i-2][j+2] && board[i-2][j+2] == board[i-3][j+3] && (board[i][j] == 'X' || board[i][j] == 'O')) {
                    winStatus = board[i][j] == 'X' ? 3 : 2;
                    return true;
                }
            }

        }
    }
    return false;
}

void display() {
    cout << "+-----------------+" << endl;
    for (int i = 0; i < 8; i++) {
        cout << "| ";
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "+-----------------+" << endl;
    cout << "  1 2 3 4 5 6 7 8" << endl;
}

void initialiseBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
}

int connect4Start() {
    initialiseBoard();
    display();
    bool gameWon = false;
    char currentPlayer = 'X';
    while (!gameWon) {
        int slot = 0;
        slot = userInput(1, 8);

        while (board[0][slot - 1] != ' ') {
            cout << "That column is full. Please try again." << endl;
            slot = userInput(1, 8);
        }

        for (int i = 7; i >= 0; i--) {
            if (board[i][slot - 1] == ' ') {
                board[i][slot - 1] = currentPlayer;
                break;
            }
        }
        gameWon = checkWin();
        display();
        currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
    }
    return winStatus;
}

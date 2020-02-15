#include <iostream>
#include <sstream>

using namespace std;

class Board {
private:
    char gameBoard[9];
    char winner;
    bool gameWon;



public:

    Board() {
        gameWon = false;
        winner = ' ';
        for (int i = 0; i < 9; i++) {
            gameBoard[i] = ' ';
        }
    }

    enum InputType {restart, position};

    int playerInput();

    int computerInput();

    void addToBoard();

    void draw();

    int computerAI();

    bool inputCheck(string input, InputType type) {
        switch (type) {
            case restart:
                return (input == "YES" || input == "NO") ? true : false;
                break;
            case position:
                if (input == "1" || input == "2" || input == "3" ||
                    input == "4" || input == "5" || input == "6" ||
                    input == "7" || input == "8" || input == "9") {
                    int playerPosInt;
                    stringstream convertTemp(input);
                    convertTemp >> playerPosInt;
                    return gameBoard[playerPosInt - 1] == ' ' ? true : false;
                }
                else {
                    return false;
                }
                break;
        }
        return false;
    }

    bool winCheck(char player) {
        if ((gameBoard[0] == gameBoard[1] && gameBoard [1] == gameBoard[2] && (gameBoard [0] == 'X' || gameBoard [0] == 'O'))
            || (gameBoard[3] == gameBoard[4] && gameBoard [4] == gameBoard[5] && (gameBoard [3] == 'X' || gameBoard [3] == 'O'))
            || (gameBoard[6] == gameBoard[7] && gameBoard [7] == gameBoard[8] && (gameBoard [6] == 'X' || gameBoard [6] == 'O'))
            || (gameBoard[0] == gameBoard[3] && gameBoard [3] == gameBoard[6] && (gameBoard [0] == 'X' || gameBoard [0] == 'O'))
            || (gameBoard[1] == gameBoard[4] && gameBoard [4] == gameBoard[7] && (gameBoard [1] == 'X' || gameBoard [1] == 'O'))
            || (gameBoard[2] == gameBoard[5] && gameBoard [5] == gameBoard[8] && (gameBoard [2] == 'X' || gameBoard [2] == 'O'))
            || (gameBoard[0] == gameBoard[4] && gameBoard [4] == gameBoard[8] && (gameBoard [0] == 'X' || gameBoard [0] == 'O'))
            || (gameBoard[2] == gameBoard[4] && gameBoard [4] == gameBoard[6] && (gameBoard [2] == 'X' || gameBoard [2] == 'O'))) {
            gameWon = true;
            setWinner(player);
            return true;
        }

        for (char x : gameBoard) {
            if (x == ' ') {
                return false;
            }
        }
        gameWon = true;
        return true;
    }

    char* getGameBoard() {
        return (char*) gameBoard;
    }

    char getWinner() {
        return winner;
    }

    bool getGameWon() {
        return gameWon;
    }

    void setWinner(char currentPlayer) {
        winner = currentPlayer;
    }
};
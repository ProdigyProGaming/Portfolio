#include <iostream>
#include "TicTacToeClasses/SmallGame.cpp"
#include "TicTacToeClasses/LargeGame.cpp"

using namespace std;

int setScore(char winner) {
    //Look at main scoreEdit function for number meanings
    int scoreType;
    if (winner == ' ') {
        scoreType = 4;
    }
    else if (winner == 'X') {
        scoreType = 3;
    }
    else {
        scoreType = 2;
    }
    return scoreType;
}

char smallGameRun() {
    SmallGame smallGameBoard;
    smallGameBoard.draw();
    while (!smallGameBoard.getGameWon()) {
        smallGameBoard.setPlayer();
        int playerPos = smallGameBoard.playerInput(1);
        smallGameBoard.addToBoard(playerPos);
        smallGameBoard.winCheck(smallGameBoard.getPlayer());
        smallGameBoard.draw();
    }
    smallGameBoard.getWinner() == ' ' ? cout << "The game is a tie" : cout << "The winner is " << smallGameBoard.getWinner() << endl;
    return smallGameBoard.getWinner();

}

char largeGameRun() {
    bool first = true;
    int previousInput;
    LargeGame largeGameBoard;
    largeGameBoard.draw();
    while (!largeGameBoard.getGameWon(2)) {
        largeGameBoard.setPlayer();

        if (first || largeGameBoard.getGameWon(1)) {
            if (!first) {
                cout << "That small board has been won" << endl;
            }
            int smallBoard = largeGameBoard.playerInput(2);
            largeGameBoard.setActiveBoard(smallBoard);
        }
        else {
            largeGameBoard.setActiveBoard(previousInput);
        }
        cout << "+-------------------+\n" <<
             "| Current Player: " << largeGameBoard.getPlayer() << " |\n" <<
             "| Active Board: " << largeGameBoard.getActiveBoard() + 1 << "   |\n" <<
             "+-------------------+" << endl;

        int playerPos = largeGameBoard.playerInput(1);
        previousInput = playerPos;
        largeGameBoard.addToBoard(playerPos, 1);
        largeGameBoard.winCheck(1);
        if (largeGameBoard.getGameWon(1)) {
            largeGameBoard.addToBoard(largeGameBoard.getActiveBoard(), 2);
        }
        largeGameBoard.winCheck(2);
        system("CLS");
        largeGameBoard.draw();
        first = false;
        largeGameBoard.setActiveBoard(playerPos);
    }
    largeGameBoard.getWinner() == ' ' ? cout << "The game is a tie" : cout << "The winner is " << largeGameBoard.getWinner() << endl;
    return largeGameBoard.getWinner();
}



int ticTacToeStart() {
    char winner = smallGameRun();
    return setScore(winner);
}
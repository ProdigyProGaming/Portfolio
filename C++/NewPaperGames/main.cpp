#include <iostream>
#include "CommonFunctions.cpp"
#include "Hangman.h"
#include "RockPaperScissors.h"
#include "Connect4.h"
#include "Battleship.h"
#include "TicTacToe.cpp"
#include "AccountManager.h"


using namespace std;

string user;
string user2;

void login() {
    cout << "How many players? 1 or 2: ";
    string userArray[] = {user, user2};
    int numberOfPlayers = userInput(1, 2);
    cout << endl;
    for (int i = 0; i < numberOfPlayers; i++) {
        cout << "Enter player username: ";
        cin >> userArray[i];
        cout << endl;
        if (!accountExists(userArray[i])) {
            cout << "The account does not exist" << endl;
            cout << "Creating account with given name..." << endl;
            createAccount(userArray[i]);
        }
        cout << userArray[i] << " Logged In" << endl;
        displayAccount(userArray[i]);
    }
    cout << endl;
}

void scoreEdit(int gameReturnValue) {
    //0 - Player 1 Lost, AI Won
    //1 - Player 1 Won, AI Lost
    //2 - Player 1 Lost, Player 2 Won
    //3 - Player 1 Won, Player 2 Lost
    //4 - Tie
    if (gameReturnValue == 0) {
        editScore(2, user);
    }
    else if (gameReturnValue == 1) {
        editScore(1, user);
    }
    else if (gameReturnValue == 2 && user2 != "") {
        editScore(2, user);
        editScore(2, user2);
    }
    else if (gameReturnValue == 3 && user2 != "") {
        editScore(1, user);
        editScore(2, user2);
    }
    else if (gameReturnValue == 4) {
        editScore(3, user);
        if (user2 != "") {
            editScore(3, user2);
        }
    }
    else {
        cout << "ERROR" << endl;
    }
}

int main() {
    login();
    int numberOfGames = 5;
    bool finished = false;
    int gameReturn;
    while (!finished) {
        cout << "Welcome to paper games" << endl;
        cout << "1 - Hangman" << endl;
        cout << "2 - Rock Paper Scissors" << endl;
        cout << "3 - Connect 4" << endl;
        cout << "4 - Battleships" << endl;
        cout << "5 - Tic Tac Toe" << endl;
        cout << "Input: ";

        int game = 0;
        game = userInput(1, numberOfGames);

        cout << endl;

        switch (game) {
            case 1:
                cout << "Hangman game selected" << endl;
                gameReturn = hangmanStart();
                break;
            case 2:
                cout << "Rock Paper Scissors selected" << endl;
                gameReturn = rockPaperScissorsStart();
                break;
            case 3:
                cout << "Connect 4 selected" << endl;
                gameReturn = connect4Start();
                break;
            case 4:
                cout << "Battleship selected" << endl;
                gameReturn = battleshipsStart();
                break;
            case 5:
                cout << "Tic Tac Toe selected" << endl;
                gameReturn = ticTacToeStart();
                break;
        }
        scoreEdit(gameReturn);
        cout << "Play another game?\n1 - Yes\n2 - No" << endl;
        finished = (userInput(1, 2) == 1) ? false : true;
    }

    cout << "Thank you for playing" << endl;

    return 0;
}

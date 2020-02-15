//
// Created by Arron on 21/12/2019.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "RockPaperScissors.h"
#include "CommonFunctions.h"

using namespace std;

string options[3]{"ROCK", "PAPER", "SCISSORS"};

int computerSelection() {
    int computerChoice = rand() % 3 + 1;
    return computerChoice;
}

int rockPaperScissorsStart() {
    int winStatus;
    cout << "Welcome to Rock Paper Scissors" << endl;
    string outcome;
    int computerChoice;
    int userChoice;

    srand(time(NULL));
    computerChoice = computerSelection();

    cout << "Please enter\n1 - Rock\n2 - Paper\n3 - Scissors" << endl;
    cout << "Input: ";

    userChoice = userInput(1, 3);

    if (userChoice == computerChoice) {
        outcome = "It's a draw!";
        winStatus = 4;
    }
    else if ((userChoice == 1 && computerChoice == 3) || (userChoice == 2 && computerChoice == 1) || (userChoice == 3 && computerChoice == 2)) {
        outcome = "You win!";
        winStatus = 1;
    }
    else {
        outcome = "You lose!";
        winStatus = 0;
    }
    cout << endl;
    cout << "You Picked - " << options[userChoice - 1] << endl;
    cout << "Computer Picked - " << options[computerChoice - 1] << endl;

    cout << outcome << endl;
    cout << endl;
    return winStatus;
}


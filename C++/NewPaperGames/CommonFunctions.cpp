//
// Created by Arron on 19/01/2020.
//

#include "CommonFunctions.h"

using namespace std;

int userInput(int lowerBound, int upperBound) {
    int userInput = 0;
    bool validInput = false;
    while (!validInput) {
        cin >> userInput;
        cin.clear();
        fflush(stdin);
        if (!(userInput >= lowerBound && userInput <= upperBound)) {
            cout << "That input is not valid" << endl;
        }
        else {
            validInput = true;
        }
    }
    return userInput;
}

//
// Created by Arron on 21/12/2019.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Hangman.h"

using namespace std;

string word;
string word2;
int stageCount = -1;
string stageArray[10]{};

void stageSetup() {
    stageArray[0] = "    _____________";
    stageArray[1] = "          |\n          |\n          |\n          |\n          |\n    ______|______";
    stageArray[2] = " __________\n         \\|\n          |\n          |\n          |\n          |\n    ______|______";
    stageArray[3] = " __________\n |       \\|\n 0        |\n          |\n          |\n          |\n    ______|______";
    stageArray[4] = " __________\n |       \\|\n 0        |\n |        |\n          |\n          |\n    ______|______";
    stageArray[5] = " __________\n |       \\|\n 0        |\n |        |\n |        |\n          |\n    ______|______";
    stageArray[6] = " __________\n |       \\|\n 0        |\n/|        |\n |        |\n          |\n    ______|______";
    stageArray[7] = " __________\n |       \\|\n 0        |\n/|\\       |\n |        |\n          |\n    ______|______";
    stageArray[8] = " __________\n |       \\|\n 0        |\n/|\\       |\n |        |\n/         |\n    ______|______";
    stageArray[9] = " __________\n |       \\|\n 0        |\n/|\\       |\n |        |\n/ \\       |\n    ______|______";
}

void readInFile() {
    ifstream myFile;
    myFile.open("..\\HangmanWords.txt");
    int count = 0;
    string line;
    int numberOfLines = 0;
    while (getline(myFile, line)) {
        numberOfLines++;
    }


    int randomWordInt = rand() % numberOfLines;
    myFile.clear();
    myFile.seekg(0);
    while (count < randomWordInt) {
        getline(myFile, word);

        count++;

    }
}

int hangmanStart() {
    int winStatus;
    stageSetup();
    srand(time(NULL));
    readInFile();

    int wordLength = word.size();
    for (int i = 0; i < wordLength; i++) {
        word2 += "_";
    }
    cout << "Current Progress: " << word2;
    bool wordGuessed = false;
    while (!wordGuessed) {
        if (stageCount == 9) {
            cout << "\nYou lose! \nThe word was " << word << endl;
            winStatus = 0;
            break;
        }
        cout << "\nPlease input horizontal: ";
        char userLetter;
        cin >> userLetter;
        cin.clear();
        fflush(stdin);
        cout << "\nLetter " << userLetter << " selected.";
        string oldWord2 = word2;
        userLetter = toupper(userLetter);
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == userLetter) {
                word2[i] = userLetter;
            }
        }
        if (oldWord2 == word2) {
            stageCount++;
        }
        cout << stageArray[stageCount] << endl;
        if (word2.find('_') == string::npos) {
            wordGuessed = true;
        }
        cout << "Current Progress: " <<  word2;
    }
    if (wordGuessed) {
        cout << "\nYou guessed the word " << word;
        winStatus = 1;
    }
    return winStatus;
}
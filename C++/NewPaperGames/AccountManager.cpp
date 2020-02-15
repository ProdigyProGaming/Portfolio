//
// Created by Arron on 21/01/2020.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include "AccountManager.h"

using namespace std;



bool createAccount(string username) {
    ofstream myFile;
    myFile.open("accounts.txt", ios::app);
    myFile << username << " " << 0 << " " << 0 << " " << 0 << "\n";
    myFile.close();

    return true;
}

void createFile() {
    ofstream outfile("accounts.txt");
    outfile.close();
}

void editScore(int scoreType, string currentUser) {
    ifstream myFile;
    ofstream writeFile;
    myFile.open("accounts.txt");
    writeFile.open("accounts1.txt");

    string line, name;
    int win, loss, tie ;
    while (getline(myFile, line)) {
        istringstream iss(line);
        if (!(iss >> name >> win >> loss >> tie )) {
            cout << "Error" << endl;
            return;
        }
        if (name == currentUser) {
            switch(scoreType) {
                case 1:
                    win++;
                    break;
                case 2:
                    loss++;
                    break;
                case 3:
                    tie++;
                    break;
            }
        }
        writeFile << name << " " << win << " " << loss << " " << tie << "\n";
    }
    myFile.close();
    writeFile.close();
    remove("accounts.txt");

    if (rename("accounts1.txt", "accounts.txt") != 0) {
        cout << "NO";
    }
}

void displayAccount(string user) {
    ifstream myFile;
    myFile.open("accounts.txt");
    if (!myFile) {
        cout << "File not Found" << endl;
    }
    string line, name;
    int win, loss, tie ;
    while (getline(myFile, line)) {
        istringstream iss(line);
        if (!(iss >> name >> win >> loss >> tie )) {
            cout << "Error" << endl;
            return;
        }
        if (name == user) {
            cout << "User " << name << ": \nWon: " << win << "\nLoss: " << loss << "\nTie: " << tie << endl;
        }
    }
}

bool accountExists(string userInput) {
    ifstream myFile;
    myFile.open("accounts.txt");
    if (!myFile) {
        cout << "File not Found" << endl;
        createFile();
        cout << "File created" << endl;
    }
    string line;
    while (getline(myFile, line)) {
        istringstream iss(line);
        string name, win, loss, tie ;
        if (!(iss >> name >> win >> loss >> tie )) {
            cout << "Error" << endl;
            return false;
        }
        if (name == userInput) {
            myFile.close();
            return true;
        }
    }
    myFile.close();
    return false;
}



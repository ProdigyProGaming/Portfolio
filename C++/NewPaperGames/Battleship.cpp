//
// Created by Arron on 21/12/2019.
//
#include "Battleship.h"
#include "CommonFunctions.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>


using namespace std;

struct CoOrd {
    int horizontal;
    int vertical;
};

struct Ship {
    int direction;
    int shipSize;
    CoOrd headPlace;
    bool sunk;
    CoOrd bodyPlaces[5];
};

vector<vector<char> > computerBoard(10, vector<char> (10, ' '));
vector<vector<char> > computerBoardView(10, vector<char> (10, ' '));
vector<vector<char> > playerBoard(10, vector<char> (10, ' '));

Ship playerShipArray[7];
Ship computerShipArray[7]{};

void initialiseShips() {
    int shipSizeArray[] = {1, 1, 2, 2, 3, 4, 5};
    Ship ship1;
    Ship ship2;
    Ship ship3;
    Ship ship4;
    Ship ship5;
    Ship ship6;
    Ship ship7;

    Ship tempShipArray[7] = {ship1, ship2, ship3, ship4, ship5, ship6, ship7};

    for (int i = 0; i < 7; i++) {
        tempShipArray[i].shipSize = shipSizeArray[i];
        tempShipArray[i].sunk = false;
        playerShipArray[i] = tempShipArray[i];
        computerShipArray[i] = tempShipArray[i];
    }
}

void displayBattleshipsBoard(bool addingShips) {
    if (!addingShips) {
        cout << "     Computers Board     " << endl;
        cout << "+-----------------------+" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "|  ";
            for (int j = 0; j < 10; j++) {
                cout << computerBoardView[i][j] << " ";
            }
            cout << " | " << i + 1;
            if (i < 7) {
                cout << "  Ship " << i + 1 << ", Length " << computerShipArray[i].shipSize << ((computerShipArray[i].sunk) ? " has been sunk!" : " has not been sunk.");
            }
            cout << endl;
        }
        cout << "+-----------------------+" << endl;
        cout << "   1 2 3 4 5 6 7 8 9 10  " << endl;
    }
    cout << "      Players Board      " << endl;
    cout << "+-----------------------+" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "|  ";
        for (int j = 0; j < 10; j++) {
            cout << playerBoard[i][j] << " ";
        }
        cout << " | " << i + 1;
        if (i < 7) {
            cout << "  Ship " << i + 1 << ", Length " << playerShipArray[i].shipSize << ((playerShipArray[i].sunk) ? " has been sunk!" : " has not been sunk.");
        }
        cout << endl;
    }
    cout << "+-----------------------+" << endl;
    cout << "   1 2 3 4 5 6 7 8 9 10  " << endl;
}

bool shipPlacementCheck(vector<vector<char>> board, Ship currentShip) {

    if (board[currentShip.headPlace.vertical][currentShip.headPlace.horizontal] != ' ') {
        return false;
    }
    for (int i = 0; i < currentShip.shipSize - 1; i++) {
        if (currentShip.bodyPlaces[i].horizontal < 0 || currentShip.bodyPlaces[i].horizontal > 9) {
            return false;
        }
        if (currentShip.bodyPlaces[i].vertical < 0 || currentShip.bodyPlaces[i].vertical > 9) {
            return false;
        }
        if (board[currentShip.bodyPlaces[i].vertical][currentShip.bodyPlaces[i].horizontal] != ' ') {
            return false;
        }
    }
    return true;
}

void replaceSunkShip(bool user, Ship shipToReplace) {
    vector<vector<char>> board = (user) ? computerBoardView : playerBoard;
    board[shipToReplace.headPlace.vertical][shipToReplace.headPlace.horizontal] = '-';
    for (int i = 0; i < shipToReplace.shipSize - 1; i++) {
        board[shipToReplace.bodyPlaces[i].vertical][shipToReplace.bodyPlaces[i].horizontal] = '-';
    }
    if (user) {
        computerBoardView = board;
    }
    else {
        playerBoard = board;
        //displayBattleshipsBoard();
    }
}

Ship shipSunkCheck(bool user, vector<vector<char>> board, Ship currentShip) {
    if (currentShip.shipSize == 1) {
        if (board[currentShip.headPlace.vertical][currentShip.headPlace.horizontal] != 'X') {
            return currentShip;
        }
    }
    else {
        if (board[currentShip.headPlace.vertical][currentShip.headPlace.horizontal] != 'X') {
            return currentShip;
        }
        else {
            for (int i = 0; i < currentShip.shipSize - 1; i++) {
                if (board[currentShip.bodyPlaces[i].vertical][currentShip.bodyPlaces[i].horizontal] != 'X') {
                    return currentShip;
                }
            }
        }
    }

    cout << ((user) ? "User " : "Computer ") << "SUNK!" << endl;
    currentShip.sunk = true;
    replaceSunkShip(user, currentShip);
    return currentShip;
}

void initialiseBattleShipsBoard() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            computerBoard[i][j] = ' ';
            playerBoard[i][j] = ' ';
            computerBoardView[i][j] = ' ';
        }
    }
}

Ship setBodyPlaces(Ship ship) {
    for (int i = 0; i < ship.shipSize - 1; i++) {
        switch (ship.direction) {
            case 1:
                ship.bodyPlaces[i].vertical = (ship.headPlace.vertical - i) - 1;
                ship.bodyPlaces[i].horizontal = ship.headPlace.horizontal;
                break;
            case 2:
                ship.bodyPlaces[i].vertical = ship.headPlace.vertical;
                ship.bodyPlaces[i].horizontal = (ship.headPlace.horizontal + i) + 1;
                break;
            case 3:
                ship.bodyPlaces[i].vertical = (ship.headPlace.vertical + i) + 1;
                ship.bodyPlaces[i].horizontal = ship.headPlace.horizontal;
                break;
            case 4:
                ship.bodyPlaces[i].vertical = ship.headPlace.vertical;
                ship.bodyPlaces[i].horizontal = (ship.headPlace.horizontal - i) - 1;
                break;
        }
    }
    return ship;
}

void placeShip(bool user, Ship shipToPlace) {
    vector<vector<char>> board;
    board = (user) ? playerBoard : computerBoard;
    board[shipToPlace.headPlace.vertical][shipToPlace.headPlace.horizontal] = 'H';
    for (int i = 0; i < shipToPlace.shipSize - 1; i++) {
        board[shipToPlace.bodyPlaces[i].vertical][shipToPlace.bodyPlaces[i].horizontal] = 'B';
    }
    if (user) {
        playerBoard = board;
    }
    else {
        computerBoard = board;
    }
}

void userInputPlaceShips(Ship* shipArray, vector<vector<char>> *board, bool userPlace) {
    for (int i = 0; i < 7; i++) {
        bool shipPlaced = false;
        while (!shipPlaced) {
            if (userPlace) {
                cout << "Ship size: " << shipArray[i].shipSize << endl;
            }
            int x, y;
            int rotation;
            if (userPlace) {
                cout << "Input Horizontal Number: ";
                x = userInput(1, 10);
                cout << endl;
                cout << "Input Vertical Number: ";
                y = userInput(1, 10);
                cout << endl;
                x--;
                y--;

                cout << "  1         2         3         4    " << endl;
                cout << "| X |   |       |   | H |   |       |" << endl;
                cout << "| X |   | H X X |   | X |   | X X H |" << endl;
                cout << "| H |   |       |   | X |   |       |" << endl;
                cout << "Input Rotation: ";
                rotation = userInput(1, 4);
            }
            else {
                x = rand() % 10;
                y = rand() % 10;
                rotation = rand() % 4 + 1;
            }

            CoOrd temp;
            temp.horizontal = x;
            temp.vertical = y;


            shipArray[i].headPlace = temp;
            shipArray[i].direction = rotation;
            shipArray[i] = setBodyPlaces(shipArray[i]);
            bool canPlace = shipPlacementCheck(*board, shipArray[i]);
            if (canPlace) {
                placeShip(userPlace, shipArray[i]);
                shipPlaced = true;
            }
            else {
                if (userPlace) {
                    cout << "Can not place ship here." << endl;
                }
            }
        }
        if (userPlace) {
            displayBattleshipsBoard(true);
        }
    }
}

CoOrd computerAIAttack() {
    int x, y;
    bool exhaustive;
    CoOrd returnCoOrd;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            exhaustive = false;
            int direction = 0;
            while (!exhaustive) {
                if (i + 1 > 9 || i - 1 < 0 || j + 1 > 9 || j - 1 < 0) {
                    exhaustive = true;
                    continue;
                }
                if (playerBoard[i][j] == 'X') {
                    int count = 1;
                    while (playerBoard[i+count][j] == 'X') {
                        if (i + count + 1 < 10) {
                            count++;
                            direction = 1;
                        }
                        if (playerBoard[i+count][j] == 'O' || playerBoard[i+count][j] == 'X') {
                            count = 1;
                            direction = 0;
                            break;
                        }
                    }
                    if (count == 1) {
                        while (playerBoard[i-count][j] == 'X') {
                            if (i - count + 1 < 10) {
                                count++;
                                direction = 2;
                            }
                            if (playerBoard[i-count][j] == 'O' || playerBoard[i-count][j] == 'X') {
                                count = 1;
                                direction = 0;
                                break;
                            }
                        }
                    }
                    if (count == 1) {
                        while (playerBoard[i][j+count] == 'X') {
                            if (j + count + 1 < 10) {
                                count++;
                                direction = 3;
                            }
                            if (playerBoard[i][j+count] == 'O' || playerBoard[i][j+count] == 'X') {
                                count = 1;
                                direction = 0;
                                break;
                            }
                        }
                    }
                    if (count == 1) {
                        while (playerBoard[i][j-count] == 'X') {
                            if (j - count + 1 < 10) {
                                count++;
                                direction = 4;
                            }
                            if (playerBoard[i][j-count] == 'O' || playerBoard[i][j-count] == 'X') {
                                count = 1;
                                direction = 0;
                                break;
                            }
                        }
                    }

                    if ((direction == 1 || direction == 0) && playerBoard[i+count][j] != 'X' && playerBoard[i+count][j] != 'O' && playerBoard[i+count][j] != '-') {
                        y = i + count;
                        x = j;
                    }
                    else if ((direction == 2 || direction == 0) && playerBoard[i-count][j] != 'X' && playerBoard[i-count][j] != 'O' && playerBoard[i-count][j] != '-') {
                        y = i - count;
                        x = j;
                    }
                    else if ((direction == 3 || direction == 0) && playerBoard[i][j+count] != 'X' && playerBoard[i][j+count] != 'O' && playerBoard[i][j+count] != '-') {
                        y = i;
                        x = j + count;
                    }
                    else if((direction == 4 || direction == 0) && playerBoard[i][j-count] != 'X' && playerBoard[i][j-count] != 'O' && playerBoard[i][j-count] != '-') {
                        y = i;
                        x = j - count;
                    }
                    else {
                        exhaustive = true;
                        continue;
                    }
                }
                else {
                    exhaustive = true;
                    continue;
                }

                if (playerBoard[y][x] != 'O' && playerBoard[y][x] != 'X' && playerBoard[y][x] != '-') {
                    returnCoOrd.horizontal = x;
                    returnCoOrd.vertical = y;
                    return returnCoOrd;
                }
                else {
                    exhaustive = true;
                }
            }
        }
    }
    bool valid = false;
    while (!valid) {
        x = rand() % 10;
        y = rand() % 10;
        if (playerBoard[y][x] != 'O' && playerBoard[y][x] != 'X' && playerBoard[y][x] != '-') {
            returnCoOrd.horizontal = x;
            returnCoOrd.vertical = y;
            valid = true;
        }
    }
    return returnCoOrd;

}

void attack(Ship* array, bool userAttack) {
    vector<vector<char>> board;
    vector<vector<char>> boardView;
    board = (userAttack) ? computerBoard : playerBoard;
    boardView = (userAttack) ? computerBoardView : playerBoard;
    int x, y;
    if (userAttack) {
        bool valid = false;
        while (!valid) {
            cout << "Input Horizontal Attack Number: ";
            x = userInput(1, 10);
            cout << endl;
            cout << "Input Vertical Attack Number: ";
            y = userInput(1, 10);
            cout << endl;
            x--;
            y--;
            if (boardView[y][x] != 'O' && boardView[y][x] != 'X' && boardView[y][x] != '-') {
                valid = true;
            }
            else {
                cout << "That is not a valid input. Please try again." << endl;
            }
        }
    }
    else {
        CoOrd tempCoOrd = computerAIAttack();
        x = tempCoOrd.horizontal;
        y = tempCoOrd.vertical;
    }
    cout << ((userAttack) ? "User " : "Computer ") << "Attacked\nX - " << x + 1 << "\nY - " << y + 1 << endl;
    if (board[y][x] != ' ' && boardView[y][x] != 'O' && boardView[y][x] != 'X') {
        cout << ((userAttack) ? "User " : "Computer ") << "HIT!" << endl;
        boardView[y][x] = 'X';
        if (userAttack) {
            computerBoard = board;
            computerBoardView = boardView;
        }
        else {
            playerBoard = boardView;
        }
        for (int i = 0; i < 7; i++) {

            for (int j = 0; j < array[i].shipSize; j++) {
                if (j == 0) {
                    if (array[i].headPlace.horizontal == x && array[i].headPlace.vertical == y) {
                        array[i] = shipSunkCheck(userAttack, boardView, array[i]);
                    }
                }
                if (j >= 0) {
                    if (array[i].bodyPlaces[j].horizontal == x && array[i].bodyPlaces[j].vertical == y) {
                        array[i] = shipSunkCheck(userAttack, boardView, array[i]);
                    }
                }
            }
        }
    }
    else {
        cout << ((userAttack) ? "User " : "Computer ") << "MISS!" << endl;
        boardView[y][x] = 'O';
        if (userAttack) {
            computerBoard = board;
            computerBoardView = boardView;
        }
        else {
            playerBoard = boardView;
        }
    }
}

int winCheck() {
    int computerCount = 0;
    int playerCount = 0;
    for (int i = 0; i < 7; i++) {
        if (computerShipArray[i].sunk == true) {
            playerCount++;
        }
        if (playerShipArray[i].sunk == true) {
            computerCount++;
        }
    }
    if (computerCount == 7) {
        return 1;
    }
    if (playerCount == 7) {
        return 2;
    }
    return 0;

}



int battleshipsStart() {
    srand(time(NULL));
    initialiseBattleShipsBoard();
    initialiseShips();

    userInputPlaceShips(computerShipArray, &computerBoard, false);
    displayBattleshipsBoard(false);
    userInputPlaceShips(playerShipArray, &playerBoard, true);

    int winStatus;
    bool won = false;
    int whoWon = 0;
    while (!won) {
        attack(computerShipArray, true);
        //displayBattleshipsBoard();

        whoWon = winCheck();
        if (whoWon != 0) {
            won = true;
        }
        else {
            attack(playerShipArray, false);
            displayBattleshipsBoard(false);
            whoWon = winCheck();
            if (whoWon != 0) {
                won = true;
            }
            else {
                won = false;
            }
        }
    }
    if (whoWon == 2) {
        winStatus = 1;
        cout << "You Won" << endl;
    }
    else {
        winStatus = 0;
        cout << "You Lost" << endl;
    }
    cout << "     Computers Board     " << endl;
    cout << "+-----------------------+" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "|  ";
        for (int j = 0; j < 10; j++) {
            if (computerBoardView[i][j] == '-') {
                computerBoard[i][j] = '-';
            }
            if (computerBoardView[i][j] == 'X') {
                computerBoard[i][j] = 'X';
            }
            if (computerBoardView[i][j] == 'O') {
                computerBoard[i][j] = 'O';
            }
            cout << computerBoard[i][j] << " ";
        }
        cout << " | " << i + 1;
        cout << endl;
    }
    cout << "+-----------------------+" << endl;
    cout << "   1 2 3 4 5 6 7 8 9 10  " << endl;
    return winStatus;
}
#include "Board.cpp"
using namespace std;

class SmallGame : public Board {
    private:
        char currentPlayer;
    public:
        SmallGame() {
            currentPlayer = 'O';
        }

        int playerInput(int type) {
            bool inputValid = false;
            string userInputPos = "";
            int playerPosInt = -1;

            while (!inputValid) {
                type == 1 ? cout << "Input position: " : cout << "Input grid: ";
                cin >> userInputPos;
                cout << endl;
                inputValid = inputCheck(userInputPos, position);
                if (!inputValid) {
                    cout << "That is not valid" << endl;
                }
            }

            stringstream convertTemp(userInputPos);
            convertTemp >> playerPosInt;
            return playerPosInt;
        }

        int computerInput() {
            return 0;
        }

        void addToBoard(int playerPos) {
            char* gameBoard = getGameBoard();
            gameBoard[playerPos - 1] = currentPlayer;
        }

        void addToBoard(int playerPos, char player) {
            char* gameBoard = getGameBoard();
            gameBoard[playerPos - 1] = player;
        }

        void draw() {
            char* gameBoard = getGameBoard();
            cout << "\n+-----+\n" <<
                 "|" << gameBoard[0] << "|" << gameBoard[1] << "|" << gameBoard[2] << "|\n" <<
                 "+-----+\n" <<
                 "|" << gameBoard[3] << "|" << gameBoard[4] << "|" << gameBoard[5] << "|\n" <<
                 "+-----+\n" <<
                 "|" << gameBoard[6] << "|" << gameBoard[7] << "|" << gameBoard[8] << "|\n" <<
                 "+-----+\n" << endl;
        }

        char getPlayer() {
            return currentPlayer;
        }
        void setPlayer() {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

};
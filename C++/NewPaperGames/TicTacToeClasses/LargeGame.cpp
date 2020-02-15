using namespace std;

class LargeGame {
    private:
        SmallGame overallLargeBoard;
        char currentPlayer;
        int activeBoard;
        SmallGame largeGameBoard[9];
    public:
        LargeGame() {
            currentPlayer = 'O';
        }

        int playerInput(int type) {
            int playerPosInt;
            switch (type) {
                case 1:
                    playerPosInt = largeGameBoard[activeBoard].playerInput(1);
                    break;
                case 2:
                    playerPosInt = overallLargeBoard.playerInput(2);
                    break;
            }
            return playerPosInt;
        }

        int computerInput() {
            return 0;
        }

        void addToBoard(int playerPos, int type) {
            switch (type) {
                case 1:
                    largeGameBoard[activeBoard].addToBoard(playerPos, currentPlayer);
                    break;
                case 2:
                    overallLargeBoard.addToBoard(activeBoard + 1, currentPlayer);
                    break;
            }
        }

        bool winCheck(int type) {
            switch (type) {
                case 1:
                    return largeGameBoard[activeBoard].winCheck(currentPlayer);
                    break;
                case 2:
                    return overallLargeBoard.winCheck(currentPlayer);
                    break;
            }
            return false;
        }

        void draw() {
            overallLargeBoard.draw();
            for (int i = 0; i < 9; i = i + 3) {
                cout << "+---------+---------+---------+\n";
                char *gameBoard1 = largeGameBoard[i].getGameBoard();
                char *gameBoard2 = largeGameBoard[i + 1].getGameBoard();
                char *gameBoard3 = largeGameBoard[i + 2].getGameBoard();
                for (int j = 0; j < 9; j = j + 3) {
                    cout << "| +-----+ | +-----+ | +-----+ |\n";
                    cout << "| |" << gameBoard1[j] << "|" << gameBoard1[j + 1] << "|" << gameBoard1[j + 2] << "| | " <<
                            "|" << gameBoard2[j] << "|" << gameBoard2[j + 1] << "|" << gameBoard2[j + 2] << "| | " <<
                            "|" << gameBoard3[j] << "|" << gameBoard3[j + 1] << "|" << gameBoard3[j + 2] << "| |" << endl;
                }
                cout << "| +-----+ | +-----+ | +-----+ |\n";
            }
            cout << "+---------+---------+---------+\n";
        }

        bool getGameWon(int type) {
            switch(type) {
                case 1:
                    return largeGameBoard[activeBoard].getGameWon();
                    break;
                case 2:
                    return overallLargeBoard.getGameWon();
                    break;
            }
            return false;
        }

        char getPlayer() {
            return currentPlayer;
        }
        void setPlayer() {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        int getActiveBoard() {
            return activeBoard;
        }
        void setActiveBoard(int input) {
            activeBoard = input - 1;
        }

        char getWinner() {
            return overallLargeBoard.getWinner();
        }
};
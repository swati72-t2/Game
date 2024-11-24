#include <iostream>
#include <vector>
using namespace std;

// Board class definition
class Board {
private:
    vector<char> board;

public:
    // Constructor to initialize the board
    Board() : board(9, ' ') {}

    // Method to display the board
    void display() const {
        cout << "\n";
        for (int i = 0; i < 9; i++) {
            cout << " " << (board[i] == ' ' ? char('1' + i) : board[i]) << " ";
            if (i % 3 != 2) cout << "|";
            else if (i != 8) cout << "\n---|---|---\n";
        }
        cout << "\n\n";
    }

    // Method to check if a cell is empty
    bool isCellEmpty(int index) const {
        return board[index] == ' ';
    }

    // Method to set a cell
    void setCell(int index, char mark) {
        board[index] = mark;
    }

    // Method to check for a win
    bool checkWin(char player) const {
        const int winConditions[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
            {0, 4, 8}, {2, 4, 6}             // Diagonals
        };
        for (const auto& condition : winConditions) {
            if (board[condition[0]] == player &&
                board[condition[1]] == player &&
                board[condition[2]] == player) {
                return true;
            }
        }
        return false;
    }

    // Method to check for a draw
    bool isDraw() const {
        for (const char& cell : board) {
            if (cell == ' ') {
                return false; // Empty cell found, not a draw
            }
        }
        return true; // No empty cells, it's a draw
    }
};

// Game class definition
class Game {
private:
    Board board;
    char currentPlayer;

public:
    // Constructor to initialize the game
    Game() : currentPlayer('X') {}

    // Method to switch the player
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Method to handle player input and update the board
    void playerMove() {
        int move;
        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> move;

            if (move >= 1 && move <= 9 && board.isCellEmpty(move - 1)) {
                board.setCell(move - 1, currentPlayer);
                break;
            } else {
                cout << "Invalid move! Please choose an empty cell (1-9).\n";
            }
        }
    }

    // Method to check for game over
    bool isGameOver() {
        if (board.checkWin(currentPlayer)) {
            board.display();
            cout << "Player " << currentPlayer << " wins!\n";
            return true;
        } else if (board.isDraw()) {
            board.display();
            cout << "It's a draw!\n";
            return true;
        }
        return false;
    }

    // Method to run the game
    void run() {
        cout << "Welcome to Tic-Tac-Toe!\n";
        while (true) {
            board.display();
            playerMove();
            if (isGameOver()) break;
            switchPlayer();
        }
    }
};

// Main function
int main() {
    Game game;
    game.run();
    return 0;
}

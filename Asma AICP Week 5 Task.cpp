#include<iostream>
using namespace std;

// Initializing the board as an array of characters
char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// Now defining the winning combinations using pairs of rows and column indices
int winning_combinations[8][3] = {{0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {0, 1, 2}, {0, 0, 2}, {0, 1, 2}, {0, 1, 2}, {2, 1, 0}}; // these represent rows, columns, and diagonals

// Next, we need a function to display the tic tac toe board
void display_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) {
                cout << "|";
            }
        }
        cout << endl;
        if (i < 2) {
            cout << "-------" << endl;
        }
    }
}

// Now we need a function to check if a player has won
bool check_winner(char player) {
    for (int i = 0; i < 8; ++i) {
        if (board[winning_combinations[i][0]][winning_combinations[i][1]] == player &&
            board[winning_combinations[i][1]][winning_combinations[i][2]] == player &&
            board[winning_combinations[i][2]][winning_combinations[i][0]] == player) {
            return true;
        }
    }
    return false;
}

// Now we need a function to check if the board is full
bool is_board_full() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false; // this means that a cell is empty so the board cannot be full
            }
        }
    }
    return true; // board is full
}

// Now for the main body to put it all together
int main() {
    // Main game loop
    char current_player = 'X';
    while (true) {
        // Display the current state of the board
        display_board();
        // Getting the player's move
        int row, col;
        cout << "Player " << current_player << " Enter your move (row and column, e.g., 1,2): ";
        cin >> row >> col;
        row--; // Adjusting to 0-based index
        col--;
        // Check if chosen space is empty
        if (board[row][col] == ' ') {
            board[row][col] = current_player;
        } else {
            cout << "Invalid move. The space is taken already. Please try again..." << endl;
            continue;
        }
        // Checking if the current player has won
        if (check_winner(current_player)) {
            // Display the final state of the board and declare the winner
            display_board();
            cout << "Player " << current_player << " wins!" << endl;
            break;
        }
        // Checking if there is a tie
        if (is_board_full()) {
            display_board();
            cout << "TIE!" << endl;
            break;
        }
        // Switching to the next player
        current_player = (current_player == 'X') ? 'O' : 'X';
    }
    return 0;
}
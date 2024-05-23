#include <iostream>
#include <vector>

using namespace std;

void printBoard(const vector<char>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            char cell = board[i * 3 + j];
            if (cell == '.') {
                cout << "_";
            } else {
                cout << cell;
            }
            if (j < 2) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

bool isValidMove(const vector<char>& board, int row, int col) {
    return board[row * 3 + col] == '.';
}

void makeMove(vector<char>& board, int player, int row, int col) {
    char symbol;
    if (player == 0) {
        symbol = 'x';
    } else {
        symbol = 'o';
    }

    board[row * 3 + col] = symbol;
}


int main() {
    string input;
    cin >> input;

    vector<char> board(input.begin(), input.end());

    int player, row, col;
    cin >> player >> row >> col;

    if (isValidMove(board, row, col)) {
        makeMove(board, player, row, col);
        printBoard(board);
    }

    return 0;
}

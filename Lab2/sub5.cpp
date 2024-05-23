#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

bool checkWin(const vector<char>& board, char player) {
    //check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player) ||
            (board[i] == player && board[i + 3] == player && board[i + 6] == player)) {
            return true;
        }
    }

    //check diagonals
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        return true;
    }

    return false;
}

//check if the board is full
bool isBoardFull(const vector<char>& board) {
    return count(board.begin(), board.end(), '.') == 0;
}

//evaluate the current state of the board
int evaluateBoard(const vector<char>& board) {
    if (checkWin(board, 'x')) {
        return 10;  //player X wins
    } else if (checkWin(board, 'o')) {
        return -10; //player O wins
    } else {
        return 0;   //draw
    }
}

//minimax function to find the optimal move
int minimax(vector<char>& board, int depth, bool isMaximizing) {
    int score = evaluateBoard(board);

    if (score == 10 || score == -10) {
        return score;
    }

    if (isBoardFull(board)) {
        return 0;
    }

    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == '.') {
                board[i] = 'x';
                best = max(best, minimax(board, depth + 1, !isMaximizing));
                board[i] = '.';  //undo the move
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == '.') {
                board[i] = 'o';
                best = min(best, minimax(board, depth + 1, !isMaximizing));
                board[i] = '.';  //undo the move
            }
        }
        return best;
    }
}

//determine the winner using the Minimax algorithm
char determineWinner(vector<char>& board) {
    int bestVal = INT_MIN;
    int bestMove = -1;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == '.') {
            board[i] = 'x';
            int moveVal = minimax(board, 0, false);
            board[i] = '.';  //undo the move

            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }

    if (bestVal == 10) {
        return 'X';
    } else if (bestVal == -10) {
        return 'O';
    } else {
        return 'D';
    }
}

int main() {
    string input;
    cin >> input;
    vector<char> board(input.begin(), input.end());

    char winner = determineWinner(board);

    if (winner == 'X') {
        cout << "X wins" << endl;
    } else if (winner == 'O') {
        cout << "O wins" << endl;
    } else {
        cout << "Draw" << endl;
    }

    return 0;
}

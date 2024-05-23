#include <iostream>
#include <vector>
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

int main() {
    string input;
    cin >> input;
    vector<char> board(input.begin(), input.end());

    //check game status
    bool xWins = checkWin(board, 'x');
    bool oWins = checkWin(board, 'o');
    bool isDraw = !xWins && !oWins && count(board.begin(), board.end(), '.') == 0;

    //print winner
    if (xWins) {
        cout << "X wins" << endl;
    } else if (oWins) {
        cout << "O wins" << endl;
    } else if (isDraw) {
        cout << "Draw" << endl;
    } else {
        cout << "In progress" << endl;
    }

    return 0;
}

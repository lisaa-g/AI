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

int main() {
    string input;
    cin >> input;

    vector<char> board(input.begin(), input.end());
    printBoard(board);

    return 0;
}

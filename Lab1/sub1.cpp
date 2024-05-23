#include <iostream>
#include <string>

using namespace std;

void printBoard(const string& input) {
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << input[index] << " ";
            ++index;
        }
        cout << endl;
    }
}

int main() {
    string input;
    cin >> input;
    printBoard(input);
    return 0;
}

#include <iostream>
#include <string>

using namespace std;

const int SIZE = 4;

int findIndex(const string& config, char ch) {
    for (int i = 0; i < SIZE * SIZE; ++i) {
        if (config[i] == ch)
            return i;
    }
    return -1; // Character not found
}

void performAction(string& config, const string& action) {
    int index = findIndex(config, '#');
    int row = index / SIZE;
    int col = index % SIZE;

    if (action == "UP" && row > 0) {
        swap(config[index], config[index - SIZE]);
    } else if (action == "DOWN" && row < SIZE - 1) {
        swap(config[index], config[index + SIZE]);
    } else if (action == "LEFT" && col > 0) {
        swap(config[index], config[index - 1]);
    } else if (action == "RIGHT" && col < SIZE - 1) {
        swap(config[index], config[index + 1]);
    }
}

void printBoard(const string& config) {
    for (int i = 0; i < SIZE * SIZE; ++i) {
        cout << config[i] << " ";
        if ((i + 1) % SIZE == 0)
            cout << endl;
    }
}

int main() {
    string config, action;
    getline(cin, config);
    getline(cin, action);

    performAction(config, action);
    printBoard(config);

    return 0;
}

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

bool allowedActions(int index, const string& action) {
    int row = index / SIZE;
    int col = index % SIZE;

    if (action == "UP" && row > 0) {
        return true;
    } else if (action == "DOWN" && row < SIZE - 1) {
        return true;
    } else if (action == "LEFT" && col > 0) {
        return true;
    } else if (action == "RIGHT" && col < SIZE - 1) {
        return true;
    }

    return false;
}

void printAvailableActions(const string& config) {
    int index = findIndex(config, '#');

    if (allowedActions(index, "UP")) {
        cout << "UP" << endl;
    }
    if (allowedActions(index, "DOWN")) {
        cout << "DOWN" << endl;
    }
    if (allowedActions(index, "LEFT")) {
        cout << "LEFT" << endl;
    }
    if (allowedActions(index, "RIGHT")) {
        cout << "RIGHT" << endl;
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
    string config;
    getline(cin, config);

    printAvailableActions(config);

    return 0;
}

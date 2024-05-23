#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

const int SIZE = 4;

struct State {
    string config;
    int cost;
};

int findIndex(const string& config, char ch) {
    for (int i = 0; i < SIZE * SIZE; ++i) {
        if (config[i] == ch)
            return i;
    }
    return -1; //character not found
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

bool isGoalState(const string& config) {
    return config == "ABCDEFGHIJKLMNO#";
}

int bfs(const string& initialConfig) {
    queue<State> q;
    unordered_set<string> visited;

    q.push({initialConfig, 0});
    visited.insert(initialConfig);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (isGoalState(current.config)) {
            return current.cost;
        }

        int index = findIndex(current.config, '#');

        //UP
        if (allowedActions(index, "UP")) {
            //create a copy of the current configuration
            string nextConfig = current.config;
            //swap the '#' symbol with the character above it
            swap(nextConfig[index], nextConfig[index - SIZE]);
            //check if the new configuration has not been visited
            if (visited.find(nextConfig) == visited.end()) {
                //push the new state (configuration and cost) into the queue
                q.push({nextConfig, current.cost + 1});
                //mark new configuration as visited
                visited.insert(nextConfig);
            }
        }

        //DOWN
        if (allowedActions(index, "DOWN")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index + SIZE]);
            if (visited.find(nextConfig) == visited.end()) {
                q.push({nextConfig, current.cost + 1});
                visited.insert(nextConfig);
            }
        }

        //LEFT
        if (allowedActions(index, "LEFT")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index - 1]);
            if (visited.find(nextConfig) == visited.end()) {
                q.push({nextConfig, current.cost + 1});
                visited.insert(nextConfig);
            }
        }

        //RIGHT
        if (allowedActions(index, "RIGHT")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index + 1]);
            if (visited.find(nextConfig) == visited.end()) {
                q.push({nextConfig, current.cost + 1});
                visited.insert(nextConfig);
            }
        }
    }

    return -1; // No solution found
}

int main() {
    string config;
    getline(cin, config);
    int moves = bfs(config);
    cout << moves << endl;

    return 0;
}

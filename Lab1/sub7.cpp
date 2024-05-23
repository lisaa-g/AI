/*#include <iostream>
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

int nodesExpanded = 0; // Counter for nodes expanded
int nExplored = 0;

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

bool isGoalState(const string& config) {
    return config == "ABCDEFGHIJKLMNO#";
}

int bfs(const string& initialConfig) {
    queue<State> q;
    unordered_set<string> visited;
    vector<State> explored;  // Keep track of nodes that are explored and removed from the frontier

    q.push({initialConfig, 0});
    visited.insert(initialConfig);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int index = findIndex(current.config, '#');

        // Check if the current state is the goal state
        if (isGoalState(current.config)) {
            return current.cost;
        }

        nExplored = explored.size();

        // UP
        if (allowedActions(index, "UP")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index - SIZE]);
            if (visited.find(nextConfig) == visited.end()) {
                visited.insert(nextConfig);
                q.push({nextConfig, current.cost + 1});
            }
        }

        // DOWN
        if (allowedActions(index, "DOWN")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index + SIZE]);
            if (visited.find(nextConfig) == visited.end()) {
                visited.insert(nextConfig);
                q.push({nextConfig, current.cost + 1});
            }
        }

        // LEFT
        if (allowedActions(index, "LEFT")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index - 1]);
            if (visited.find(nextConfig) == visited.end()) {
                visited.insert(nextConfig);
                q.push({nextConfig, current.cost + 1});
            }
        }

        // RIGHT
        if (allowedActions(index, "RIGHT")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index + 1]);
            if (visited.find(nextConfig) == visited.end()) {
                visited.insert(nextConfig);
                q.push({nextConfig, current.cost + 1});
            }
        }

        explored.push_back(current);  // Add the explored state to the vector
    }

    return -1; // No solution found
}

int main() {
    string config;
    getline(cin, config);
    int moves = bfs(config);
    cout << "Moves: " << moves << endl;
    cout << "Nodes Expanded: " << nExplored << endl; // Display the number of nodes expanded

    return 0;
}*/

#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

const int SIZE = 4;

struct State {
    string config;
    int cost;
    int heuristic;  //heuristic value = number of misplaced tiles
};

int nExplored = 0;

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

//heuristic function h1 = number of misplaced tiles
int misplacedTilesHeuristic(const string& config) {
    int count = 0;
    for (int i = 0; i < SIZE * SIZE; ++i) {
        if (config[i] != '#' && config[i] != "ABCDEFGHIJKLMNO"[i]) {
            count++;
        }
    }
    return count;
}

//A* search
int astar(const string& initialConfig) {
    //priority queue to store states based on their total cost (f)
    priority_queue<State, vector<State>, function<bool(State, State)>> pq(
        [](State const& lhs, State const& rhs) {
            return lhs.cost + lhs.heuristic > rhs.cost + rhs.heuristic;
        });

    unordered_set<string> visited;
    vector<State> explored;  // Keep track of nodes that are explored and removed from the frontier

    pq.push({initialConfig, 0, misplacedTilesHeuristic(initialConfig)});
    visited.insert(initialConfig);

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (isGoalState(current.config)) {
            return current.cost;
        }

        nExplored = explored.size();

        int index = findIndex(current.config, '#');

        //UP
        if (allowedActions(index, "UP")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index - SIZE]);
            if (visited.find(nextConfig) == visited.end()) {
                //push the next state into the priority queue with updated cost and heuristic
                pq.push({nextConfig, current.cost + 1, misplacedTilesHeuristic(nextConfig)});
                visited.insert(nextConfig);
            }
        }

        //DOWN
        if (allowedActions(index, "DOWN")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index + SIZE]);
            if (visited.find(nextConfig) == visited.end()) {
                pq.push({nextConfig, current.cost + 1, misplacedTilesHeuristic(nextConfig)});
                visited.insert(nextConfig);
            }
        }

        //LEFT
        if (allowedActions(index, "LEFT")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index - 1]);
            if (visited.find(nextConfig) == visited.end()) {
                pq.push({nextConfig, current.cost + 1, misplacedTilesHeuristic(nextConfig)});
                visited.insert(nextConfig);
            }
        }

        //RIGHT
        if (allowedActions(index, "RIGHT")) {
            string nextConfig = current.config;
            swap(nextConfig[index], nextConfig[index + 1]);
            if (visited.find(nextConfig) == visited.end()) {
                pq.push({nextConfig, current.cost + 1, misplacedTilesHeuristic(nextConfig)});
                visited.insert(nextConfig);
            }
        }

        explored.push_back(current);  // Add the explored state to the vector
    }

    return -1; // No solution found
}

int main() {
    string config;
    getline(cin, config);
    int moves = astar(config);
    cout << moves << endl;
    cout << "Nodes Expanded: " << nExplored << endl; // Display the number of nodes expanded
    return 0;
}
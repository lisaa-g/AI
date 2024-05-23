#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const string goalState = "ABCDEFGHIJKLMNO#";

// Define moves (UP, DOWN, LEFT, RIGHT)
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};
const string moves = "UDLR";

// Function to check valid move
bool isValidMove(int row, int col) {
    return row >= 0 && row < 4 && col >= 0 && col < 4;
}

// Function to perform breadth-first search
int bfs(const string& initialState, int& nodesExpanded) {
    queue<pair<string, int>> q;
    unordered_map<string, bool> visited;
    q.push({initialState, 0});
    visited[initialState] = true;
    nodesExpanded = 0;

    while (!q.empty()) {
        string state = q.front().first;
        int cost = q.front().second;
        q.pop();

        if (state == goalState) {
            return cost;
        }

        int index = state.find('#');
        int row = index / 4;
        int col = index % 4;
        nodesExpanded++;

        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (isValidMove(newRow, newCol)) {
                int newIndex = newRow * 4 + newCol;
                string nextState = state;
                swap(nextState[index], nextState[newIndex]);

                if (!visited[nextState]) {
                    visited[nextState] = true;
                    q.push({nextState, cost + 1});
                }
            }
        }
    }

    return -1;
}

// Heuristic function h1: Number of tiles in the wrong location
int h1(const string& state) {
    int count = 0;
    for (int i = 0; i < 16; ++i) {
        if (state[i] != goalState[i])
            count++;
    }
    return count;
}

// Function to perform A* search with heuristic h1
int astar_h1(const string& initialState, int& nodesExpanded) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, int> costSoFar;
    pq.push({h1(initialState), initialState});
    costSoFar[initialState] = 0;
    nodesExpanded = 0;

    while (!pq.empty()) {
        string state = pq.top().second;
        int cost = costSoFar[state] + h1(state);
        pq.pop();
        nodesExpanded++;

        if (state == goalState) {
            return costSoFar[state];
        }

        int index = state.find('#');
        int row = index / 4;
        int col = index % 4;

        for (int i = 0; i < 4; ++i) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (isValidMove(newRow, newCol)) {
                int newIndex = newRow * 4 + newCol;
                string nextState = state;
                swap(nextState[index], nextState[newIndex]);

                int newCost = costSoFar[state] + 1;
                if (!costSoFar.count(nextState) || newCost < costSoFar[nextState]) {
                    costSoFar[nextState] = newCost;
                    pq.push({newCost + h1(nextState), nextState});
                }
            }
        }
    }

    return -1;
}

// Heuristic function h2: Sum of distances of tiles from their goal positions
int h2(const string& state) {
    int distance = 0;
    for (int i = 0; i < 16; ++i) {
        if (state[i] != '#') { 
            int goalRow = (state[i] - 'A') / 4;
            int goalCol = (state[i] - 'A') % 4;
            int currRow = i / 4;
            int currCol = i % 4;
            distance += abs(goalRow - currRow) + abs(goalCol - currCol); 
        }
    }
    return distance;
}

// Function to perform A* search with heuristic h2
int astar_h2(const string& initialState, int& nodesExpanded) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, int> costSoFar;
    pq.push({h2(initialState), initialState});
    costSoFar[initialState] = 0;
    nodesExpanded = 0;

    while (!pq.empty()) {
        string state = pq.top().second;
        int cost = costSoFar[state] + h2(state);
        pq.pop();
        nodesExpanded++;

        if (state == goalState) {
            return costSoFar[state];
        }

        int index = state.find('#');
        int row = index / 4;
        int col = index % 4;

        for (int i = 0; i < 4; ++i) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (isValidMove(newRow, newCol)) {
                int newIndex = newRow * 4 + newCol;
                string nextState = state;
                swap(nextState[index], nextState[newIndex]);

                int newCost = costSoFar[state] + 1;
                if (!costSoFar.count(nextState) || newCost < costSoFar[nextState]) {
                    costSoFar[nextState] = newCost;
                    pq.push({newCost + h2(nextState), nextState});
                }
            }
        }
    }

    return -1;
}

int main() {
    ifstream file("puzzles.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    ofstream outputFile("solutions.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to create output file." << endl;
        return 1;
    }

    outputFile << "Puzzle" << " " << "Solution" << " " << "BFS" << " " <<"A*-h1" << " " <<"A*-h2\n" << endl;

    string puzzle;
    while (getline(file, puzzle)) {
        int nodesExpanded_bfs, nodesExpanded_h1, nodesExpanded_h2;
        int shortestPathCost_bfs = bfs(puzzle, nodesExpanded_bfs);
        int shortestPathCost_h1 = astar_h1(puzzle, nodesExpanded_h1);
        int shortestPathCost_h2 = astar_h2(puzzle, nodesExpanded_h2);

        outputFile << puzzle << " " << shortestPathCost_bfs << " " << nodesExpanded_bfs << " " << nodesExpanded_h1 << " " << nodesExpanded_h2 << endl;
    }

    file.close();
    outputFile.close();

    return 0;
}

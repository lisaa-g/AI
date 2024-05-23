#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> Point;

//read a payoff matrix as pairs of integers
void readPayoffMatrix(int N, vector<vector<Point>>& payoffMatrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            char comma;
            cin >> payoffMatrix[i][j].first >> comma >> payoffMatrix[i][j].second;
        }
    }
}

//find the maximum values in each row of the payoff matrix
vector<int> maxInRows(const vector<vector<Point>>& payoffMatrix, int N) {
    vector<int> result(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i] = max(payoffMatrix[i][j].first, result[i]);
        }
    }

    return result;
}

int main() {
    int N;
    cin >> N;
    vector<vector<Point>> payoffMatrix(N, vector<Point>(N));
    readPayoffMatrix(N, payoffMatrix);

    vector<int> result = maxInRows(payoffMatrix, N);

    int rowIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (result[i] > result[rowIndex]) {
            rowIndex = i;
        }
    }

    int colIndex = 0;
    for (int j = 1; j < N; ++j) {
        if (payoffMatrix[rowIndex][j].second > payoffMatrix[rowIndex][colIndex].second) {
            colIndex = j;
        }
    }

    cout << payoffMatrix[rowIndex][colIndex].first << ',' << payoffMatrix[rowIndex][colIndex].second << endl;

    return 0;
}

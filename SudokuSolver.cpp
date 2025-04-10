#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int SIZE = 9;

class Sudoku {
private:
    int grid[SIZE][SIZE];
    vector<pair<int, int>> emptyCells;
    string fileName;

public:
    Sudoku(string file) : fileName(file) {
        ifstream inFile(file);
        if (!inFile) {
            cerr << "Failed to open " << file << endl;
            exit(1);
        }

        char ch;
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                inFile >> ch;
                if (ch == '_') {
                    grid[row][col] = 0;
                    emptyCells.push_back({ row, col });
                } else {
                    grid[row][col] = ch - '0';
                }
            }
        }
    }

    void printPuzzle() {
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (grid[row][col] == 0)
                    cout << "_ ";
                else
                    cout << grid[row][col] << " ";
            }
            cout << endl;
        }
    }

    void solve() {
        cout << "Puzzle: " << fileName << endl;
        printPuzzle();
        cout << "\nSolutions:\n";
        int count = 0;
        solveRecursive(0, count);
        if (count == 0) {
            cout << "No solution found.\n";
        }
    }

private:
    bool isValid(int row, int col, int val) {
        // Check row and column
        for (int i = 0; i < SIZE; ++i) {
            if (grid[row][i] == val || grid[i][col] == val)
                return false;
        }

        // Check 3x3 block
        int blockRow = (row / 3) * 3;
        int blockCol = (col / 3) * 3;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[blockRow + i][blockCol + j] == val)
                    return false;

        return true;
    }

    void solveRecursive(int idx, int &solutionCount) {
        if (idx == emptyCells.size()) {
            ++solutionCount;
            cout << "\nSolution " << solutionCount << ":\n";
            printPuzzle();
            return;
        }

        int row = emptyCells[idx].first;
        int col = emptyCells[idx].second;

        for (int val = 1; val <= 9; ++val) {
            if (isValid(row, col, val)) {
                grid[row][col] = val;
                solveRecursive(idx + 1, solutionCount);
                grid[row][col] = 0; // Backtrack
            }
        }
    }
};

int main() {
    string file;
    cout << "Enter the puzzle file name (e.g., puzzle1.txt): ";
    cin >> file;

    Sudoku sudoku(file);
    sudoku.solve();

    return 0;
}

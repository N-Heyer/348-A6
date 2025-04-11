/*
Author: Nick Heyer
KUID: 3142337
Date: 4/10/25
Lab: Assignment6
Last modified: 4/10/25
EECS 348 Assignment 6
Sudoku solver
input: puzzle#.txt / user input
Output:original sudoku that was given in the file and the correct solved output
Collaborators: ChatGPT was used to find syntax errors, and helped me with getting the grid down and how to make it know to change the "_" and not anything else
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int SIZE = 9;//sudoku grid size is 9x9

//class does the grid and file reading and solving logic and output
class Sudoku {
private:
    int grid[SIZE][SIZE];//soduko grid
    vector<pair<int, int>> emptyCells;//list of coords of empty cells in the grid
    string fileName;//name of file aka puzzle1.txt etc

public:
    //constructor that readss the puzzle from the file and inits grid
    Sudoku(string file) : fileName(file) {
        ifstream inFile(file);//open file
        if (!inFile) { //error if file no open
            cerr << "Failed to open " << file << endl;
            exit(1);
        }

        char ch;
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                inFile >> ch;//read each character either digit or _
                if (ch == '_') { //blank cell
                    grid[row][col] = 0;//use 0 internally for empty
                    emptyCells.push_back({ row, col });  // Track its position
                } else {
                    grid[row][col] = ch - '0'; //convert char to int
                }
            }
        }
    }

    //prints orig puzzle
    void printPuzzle() {
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (grid[row][col] == 0)
                    cout << "_ ";//use underscore for empty
                else
                    cout << grid[row][col] << " ";
            }
            cout << endl;
        }
    }

    //solve and print solution
    void solve() {
        cout << "Puzzle: " << fileName << endl;
        printPuzzle();//show init puzle
        cout << "\nSolutions:\n";
        int count = 0;
        solveRecursive(0, count);//recursive solving
        if (count == 0) {
            cout << "No solution found.\n";// prints if no sol found
        }
    }

private:
    //checks whether a value is valid in a given cell
    bool isValid(int row, int col, int val) {
        //check if val already exists in the same row or column
        for (int i = 0; i < SIZE; ++i) {
            if (grid[row][i] == val || grid[i][col] == val)
                return false;
        }

        //check 3x3 block containing the cell
        int blockRow = (row / 3) * 3;
        int blockCol = (col / 3) * 3;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[blockRow + i][blockCol + j] == val)
                    return false;

        return true;// checks to make sure it can place value
    }

    //recursive backtracking solver
    void solveRecursive(int idx, int &solutionCount) {
        if (idx == emptyCells.size()) {
            //basecase is that all cells are full
            ++solutionCount;
            cout << "\nSolution " << solutionCount << ":\n";
            printPuzzle();
            return;
        }

        //get the next empty sell coords
        int row = emptyCells[idx].first;
        int col = emptyCells[idx].second;

        //try val 1-9 in cell 
        for (int val = 1; val <= 9; ++val) {
            if (isValid(row, col, val)) {
                grid[row][col] = val;// place val
                solveRecursive(idx + 1, solutionCount); //recurse to next cell
                grid[row][col] = 0;//backtrack if needed
            }
        }
    }
};

//main func to get user input and solve puzzle with user given .txt
int main() {
    string file;

    //prompt for user file name
    cout << "Enter the puzzle file name (e.g., puzzle1.txt): ";
    cin >> file;

    //create and solve puzzle
    Sudoku sudoku(file);
    sudoku.solve();

    return 0;
}

#include <iostream>
using namespace std;

const int GRID_SIZE = 9;

// Function to print the Sudoku board
void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing num at grid[row][col] is valid
bool isValid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    // Check row
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }
    // Check column
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }
    // Check 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Recursive function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    bool isEmpty = false;

    // Find the first empty cell
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }

    // No empty cell found, puzzle solved
    if (!isEmpty) return true;

    // Try numbers 1 to 9
    for (int num = 1; num <= GRID_SIZE; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) return true;
            grid[row][col] = 0; // Reset cell if no solution found
        }
    }
    return false; // Trigger backtracking
}

int main() {
    int grid[GRID_SIZE][GRID_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku Solved Successfully:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for this Sudoku puzzle.\n";
    }

    return 0;
}
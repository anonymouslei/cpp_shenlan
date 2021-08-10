#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Sudoku {
public:
    Sudoku();
    ~Sudoku(){};

    void printSudoku();
    void printNumOfSolutions() {
        std::cout << "num of solution is: " << numOfSolutions_ << std::endl;
    };
    void readSudokuFromFile(const std::string &file_name);
    std::vector<std::vector<int>> getBoxes() { return boxes_; }
    std::vector<std::vector<int>> getRows() { return rows_; }
    std::vector<std::vector<int>> getCols() { return cols_; }
    std::vector<std::vector<int>> getSudokuBoard() { return sudoku_board_; }
    void solveSudoku();

private:
    std::vector<std::vector<int>> rows_, cols_, boxes_, sudoku_board_;
    int numOfSolutions_;

    bool helper(int row, int col);
};

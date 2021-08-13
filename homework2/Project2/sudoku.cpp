#include "sudoku.hpp"

Sudoku::Sudoku() { numOfSolutions_ = 0; }

void Sudoku::readSudokuFromFile(const std::string &file_name) {
    std::ifstream fin;
    fin.open(file_name);
    if (!fin.is_open()) {
        throw std::invalid_argument("the input is invalid!\n");
    }
    std::string line;

    int size{0};
    while (std::getline(fin, line)) {
        for (auto x : line) {
            if (x == ' ') {
                continue;
            }
            if (x != '0') {
                int n = x - '0';
                int col = size % 9;
                int row = size / 9;
                // 把每个row，col和box中已经出现过的数值存入vector。
                // 如果存在过，则就将vector相对应的地方标记为1。未出现过，则为0
                rows_[row][n] = 1;
                cols_[col][n] = 1;
                int box_r = row / 3;
                int box_c = col / 3;
                boxes_[box_r * 3 + box_c][n] = 1;
                sudoku_board_[row][col] = n;
            }
            size++;
        }
    }
}

void Sudoku::solveSudoku() { helper(0, 0); }

void Sudoku::helper(int row, int col) {
    if (col == 9) {
        numOfSolutions_++;
        return;
    }

    int next_col, next_row;
    next_row = (row + 1) % 9;

    if (next_row == 0) {
        next_col = col + 1;
    } else {
        next_col = col;
    }

    if (sudoku_board_[row][col] != 0) {
        helper(next_row, next_col);
        return;
    }

    for (size_t i = 1; i < 10; i++) {
        int box_r = row / 3;
        int box_c = col / 3;
        int box_int = box_r * 3 + box_c;
        // 如果满足条件，留下，并计算下一个
        if ((!rows_[row][i]) && (!cols_[col][i]) && (!boxes_[box_int][i])) {
            rows_[row][i] = 1;
            cols_[col][i] = 1;
            boxes_[box_int][i] = 1;
            sudoku_board_[row][col] = i;

            helper(next_row, next_col);
            // 不满足就状态返回
            rows_[row][i] = 0;
            cols_[col][i] = 0;
            boxes_[box_int][i] = 0;
            sudoku_board_[row][col] = 0;
        }
    }
}

void Sudoku::printSudoku() {
    std::cout << "sudoku result: \n";
    for (auto &i : sudoku_board_) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}


// result
median : 35;
hard : 1226;
hard + : 12660;
hard++ : 17619;

// change to array
median : 18;
hard : 602;
hard + : 5484;
hard++ : 8818;

// change to col
median : 4;
hard : 877;
hard + : 1400;
hard++ : 1902;

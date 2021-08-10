#include "sudoku.hpp"
#include <chrono>
#include <iostream>

class Solution {
public:
private:
};

int ans = 0;
int main() {
    /* read file */
    std::string file_name = "/media/sf_VirtualShared/cpp/homework2/Project2/sudo/hard++.txt";
    Sudoku test;
    test.readSudokuFromFile(file_name);

    /* start */
    std::chrono::time_point<std::chrono::system_clock> server_create_time_ =
        std::chrono::system_clock::now();
    test.solveSudoku();

    /* solve problem */

    /* end */
    std::cout << "solution_count = " << ans << std::endl;
    auto current_time = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> duration_mili = current_time - server_create_time_;
    std::cout << "PrintDuration : duration_mili duration = " << (long)duration_mili.count()
              << " ms";
    // test.printSudoku();
    test.printNumOfSolutions();
}

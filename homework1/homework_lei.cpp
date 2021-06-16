#include<iostream>
#include<fstream>
#include<string>
#include<vector>

/**
 * 1. two negative number x
 * 2. two positive number x
 * 3. 12 + 99 x
 * 4. 12 - 99 x
 * 5. +0 + +0 = 0 x
 * 7. -12 + 5 x
 */

int IsGreater(const std::vector<int>& arg1, const std::vector<int>& arg2) {
    int arg1_size = arg1.size();
    int arg2_size = arg2.size();
    if (arg1_size > arg2_size) {
        return 1;
    } else if (arg1_size < arg2_size) {
        return -1;
    }

    for (size_t i = 0; i < arg1_size; i++) {
        if (arg1.at(i) > arg2.at(i)) {
            return 1;
        } else if (arg1.at(i) < arg2.at(i)) {
            return -1;
        }
    }
    return 0;
}

void OutBounds(int& result_n, int& ten_flag) {
    if (result_n > 9) {
        ten_flag = 1;
        result_n -= 10;
    } else if (result_n >= 0){
        ten_flag = 0;
    } else {
        result_n += 10;
        ten_flag = -1;
    }
}

void StringToVector(const std::string& num_string, std::vector<int>& num_vectors, bool& positive_flag) {
    bool null_flag = true;
    for (auto i = 0; i < num_string.size(); i++) {
        char num = num_string.at(i);
        if ((i == 0) &&  (num == '-')) {
            positive_flag = false;
            continue;
        }        
        if (num == '+') {
            continue;
        }
        if (null_flag && (num == '0')) {
            continue;
        }
        null_flag = false;
        num_vectors.push_back(num - '0');
    }
    if (num_vectors.empty()) {
        num_vectors.push_back(0);
        positive_flag = true;
    }
}

std::string VectorToString(const std::vector<int>& num_vectors, const bool& positive_flag) {
    std::string out;
    if (positive_flag==0) {
        out.push_back('-');
    }
    bool null_flag = true;
    for (int i = num_vectors.size() - 1; i >= 0; i--) {
        int num = num_vectors.at(i);
        if (null_flag && (num == 0)) {
            continue;
        }
        null_flag = false;
        out.push_back('0' + num);
    }
    if (out.empty()) {
        out.push_back('0');
    }
    out.push_back('\0');
    return out;
}

void same_sign_add(const std::vector<int>& arg1, const std::vector<int>& arg2,
                   std::vector<int>& result) {
    int size_1 = arg1.size();
    int size_2 = arg2.size();
    int ten_flag = 0;

    int diff_size = (size_1 > size_2) ? size_2 : size_1;
 
    for (size_t i = 0; i < diff_size; i++) {
            int result_n = arg1.at(size_1-i-1) + arg2.at(size_2-i-1) + ten_flag;
            OutBounds(result_n, ten_flag);
            result.push_back(result_n);
    }
    
    for (size_t i = diff_size; i < size_2; i++) {
        int result_n = arg2.at(size_2-i-1) + ten_flag;
        OutBounds(result_n, ten_flag);
        result.push_back(result_n);
    }
    for (size_t i = diff_size; i < size_1; i++) {
        int result_n = arg1.at(size_1-i-1) + ten_flag;
        OutBounds(result_n, ten_flag);
        result.push_back(result_n);
    }
    if (ten_flag > 0) {
        result.push_back(ten_flag);
    }
}

void subtraction(const std::vector<int>& arg1, const std::vector<int>& arg2,
                 std::vector<int>& result) {
    int size_1 = arg1.size();
    int size_2 = arg2.size();
    int ten_flag = 0;

    int diff_size = size_2;

    for (size_t i = 0; i < diff_size; i++) {
            int result_n = arg1.at(size_1-i-1) - arg2.at(size_2-i-1) + ten_flag;
            OutBounds(result_n, ten_flag);
            result.push_back(result_n);
    }
    for (size_t i = diff_size; i < size_1; i++) {
        int result_n = arg1.at(size_1-i-1) + ten_flag;
        OutBounds(result_n, ten_flag);
        result.push_back(result_n);
    }
    if (ten_flag < 0) {
        result.push_back(-ten_flag);
    }
    
    
}

void DecimalAddition(const std::vector<int>& arg1, const bool arg1_positive,
                     const std::vector<int>& arg2, const bool arg2_positive,
                     std::vector<int>& result, bool& result_positive) {
    int size_1 = arg1.size();
    int size_2 = arg2.size();

    if (arg1_positive && arg2_positive) {
        same_sign_add(arg1, arg2, result);
        result_positive = true;
    } else if ((arg1_positive == 0) && (arg2_positive == 0)) {
        same_sign_add(arg1, arg2, result);
        result_positive = false;
    } else {
        int arg1Greater = IsGreater(arg1, arg2);
        switch (arg1Greater)
        {
        case 1:
            subtraction(arg1, arg2, result);
            result_positive = arg1_positive;
            break;
        case -1:
            subtraction(arg2, arg1, result);
            result_positive = arg2_positive;
            break;
        case 0:
            result.push_back(0);
            result_positive = 1;
        }
    }
}

int main(const int argc, const char *argv[]) {
    std::string file_name = argv[1];
    std::ifstream fin(file_name);

    std::string line;
    std::vector<std::string> num_arrays;
    
    while (std::getline(fin, line)) {
        num_arrays.push_back(line);
    } 

    bool num1_positive_flag{true}, num2_positive_flag{true};
    std::vector<int> num_array_1;
    std::vector<int> num_array_2;
    StringToVector(num_arrays[0], num_array_1, num1_positive_flag);
    StringToVector(num_arrays[1], num_array_2, num2_positive_flag);

    std::vector<int> result_array;
    bool result_flag;
    DecimalAddition(num_array_1, num1_positive_flag, num_array_2, num2_positive_flag, result_array, result_flag);

    std::string out = VectorToString(result_array, result_flag);
    std::cout << out << std::endl;
}

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<exception>

std::vector<int> FilpVector(const std::vector<int>& input) {
    std::vector<int> result;
    for (int i = input.size() - 1; i >= 0; i--) {
        result.push_back(input.at(i));
    }
    return result;
}

int StringToInt(const std::string& input) {
    if (input.size() > 2)
        throw std::logic_error("The input must be 0~36!\n");
    for (const char c: input) {
        if ((c > '9') || (c < '0')) {
            throw std::logic_error("The input must be 0~36!\n");
        }
    }
    if (input.size() < 2) {
       return (input[0] - '0');
    }
    return (input[1] - '0') + (input[0] - '0') * 10;
}

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

void OutBounds(const int& numeric, int& result_n, int& ten_flag) {
    if (result_n > numeric - 1) {
        ten_flag = 1;
        result_n -= numeric;
    } else if (result_n >= 0){
        ten_flag = 0;
    } else {
        result_n += numeric;
        ten_flag = -1;
    }
}

void StringToVector(const std::string& num_string, const int& numeric,
                    std::vector<int>& num_vectors, bool& positive_flag) {
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
        int num_i;
        if (num > 96) {
            num_i = num - 'a' + 10;
        } else if ((num > 64) && (num < 91)) {
            num_i = num - 'A' + 10;
        } else {
            num_i = num - '0';
        }
        // input is error
        if (num_i > numeric)
            throw std::logic_error("wrong input!\n");
        num_vectors.push_back(num_i);
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
        if (num > 9) {
            out.push_back('a' + (num - 10));
        } else {
            out.push_back('0' + num);
        }
    }
    if (out.empty()) {
        out.push_back('0');
    }
    return out;
}

void same_sign_add(const std::vector<int>& arg1, const std::vector<int>& arg2,
                   const int& numeric, std::vector<int>& result) {
    int size_1 = arg1.size();
    int size_2 = arg2.size();
    int ten_flag = 0;

    int diff_size = (size_1 > size_2) ? size_2 : size_1;
 
    for (size_t i = 0; i < diff_size; i++) {
            int result_n = arg1.at(size_1-i-1) + arg2.at(size_2-i-1) + ten_flag;
            OutBounds(numeric, result_n, ten_flag); 
            result.push_back(result_n);
    }
    
    for (size_t i = diff_size; i < size_2; i++) {
        int result_n = arg2.at(size_2-i-1) + ten_flag;
        OutBounds(numeric, result_n, ten_flag);
        result.push_back(result_n);
    }
    for (size_t i = diff_size; i < size_1; i++) {
        int result_n = arg1.at(size_1-i-1) + ten_flag;
        OutBounds(numeric, result_n, ten_flag);
        result.push_back(result_n);
    }
    if (ten_flag > 0) {
        result.push_back(ten_flag);
    }
}

void subtraction(const std::vector<int>& arg1, const std::vector<int>& arg2,
                 const int& numeric, std::vector<int>& result) {
    int size_1 = arg1.size();
    int size_2 = arg2.size();
    int ten_flag = 0;

    int diff_size = size_2;

    for (size_t i = 0; i < diff_size; i++) {
            int result_n = arg1.at(size_1-i-1) - arg2.at(size_2-i-1) + ten_flag;
            OutBounds(numeric, result_n, ten_flag);
            result.push_back(result_n);
    }
   
    for (size_t i = diff_size; i < size_1; i++) {
        int result_n = arg1.at(size_1-i-1) + ten_flag;
        OutBounds(numeric, result_n, ten_flag);
        result.push_back(result_n);
    }
    if (ten_flag < 0) {
        result.push_back(-ten_flag);
    }
}

void Addition(const std::vector<int>& arg1, const bool arg1_positive,
              const std::vector<int>& arg2, const bool arg2_positive,
              const int& numeric, std::vector<int>& result, bool& result_positive) {
    int size_1 = arg1.size();
    int size_2 = arg2.size();

    if (arg1_positive && arg2_positive) {
        same_sign_add(arg1, arg2, numeric, result);
        result_positive = true;
    } else if ((arg1_positive == 0) && (arg2_positive == 0)) {
        same_sign_add(arg1, arg2, numeric, result);
        result_positive = false;
    } else {
        int arg1Greater = IsGreater(arg1, arg2);
        switch (arg1Greater)
        {
        case 1:
            subtraction(arg1, arg2, numeric, result);
            result_positive = arg1_positive;
            break;
        case -1:
            subtraction(arg2, arg1, numeric, result);
            result_positive = arg2_positive;
            break;
        case 0:
            result.push_back(0);
            result_positive = 1;
        }
    }
}

std::vector<int> ConvertMToN(const std::vector<int>& input, const int M, const int N) {
    // reference:https://blog.csdn.net/Jaster_wisdom/article/details/52107785
    std::vector<int> result;
    std::vector<int> filp_input = FilpVector(input);
    std::vector<int> i = filp_input;
    std::vector<int> new_vector;
    while(true) {
        bool null_flag = true;
        int modu;
        int tmp = i.at(0);
        for (size_t j = 0; j < i.size(); j++) {
            if (j > 0) {
                tmp = tmp * M + i.at(j);
            }
            modu = tmp % N;

            int division = tmp / N;
            tmp = modu;
            if (null_flag && (division == 0)) {
                continue;
            }
            null_flag = false;
            new_vector.push_back(division);
        }
        i.clear();
        i = new_vector;
        new_vector.clear();
        result.push_back(modu);
        if (i.size() == 0) {
            break;
        }
    }
    return result;
}

int main(const int argc, const char *argv[]) {
    std::string file_name = argv[1];
    std::ifstream fin(file_name);
    std::string input_numeric_s = argv[2];
    std::string output_numeric_s = argv[3];

    int input_numeric = StringToInt(input_numeric_s);
    int output_numeric = StringToInt(output_numeric_s);

    std::string line;
    std::vector<std::string> num_arrays;
    
    while (std::getline(fin, line)) {
        num_arrays.push_back(line);
    } 

    bool num1_positive_flag{true}, num2_positive_flag{true};
    std::vector<int> num_array_1;
    std::vector<int> num_array_2;
    StringToVector(num_arrays[0], input_numeric, num_array_1, num1_positive_flag);
    StringToVector(num_arrays[1], input_numeric, num_array_2, num2_positive_flag);

    std::vector<int> result_array;
    bool result_flag;
    Addition(num_array_1, num1_positive_flag, num_array_2, num2_positive_flag, input_numeric, result_array, result_flag);

    std::vector<int> result = ConvertMToN(result_array, input_numeric, output_numeric);

    std::string out = VectorToString(result, result_flag);
    std::cout << out << std::endl;
}

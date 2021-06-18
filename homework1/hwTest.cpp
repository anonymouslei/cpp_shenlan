#include "gtest/gtest.h"
#include "homework_lei.cpp"

TEST(HWFixture, stringtoint){ 
    std::string s = "10";
    EXPECT_EQ(StringToInt(s), 10);

    std::string a = "8";
    EXPECT_EQ(StringToInt(a), 8);
}

TEST(HWFixture, stringtovector0) {
    std::string s = "-008cE";
    std::vector<int> num_vectors;
    bool positive_flag;
    StringToVector(s, 16, num_vectors, positive_flag);
    EXPECT_EQ(num_vectors[0], 8);
    EXPECT_EQ(num_vectors[1], 12);
    EXPECT_EQ(num_vectors[2], 14);
    EXPECT_EQ(positive_flag, false);
}

// TEST(HWFixture, stringtovector1) {
//     bool flag = 0;
//     try {
//         std::string s = "c";
//         std::vector<int> num_vectors;
//         bool positive_flag;
//         StringToVector(s, 10, num_vectors, positive_flag);
//     } catch (const std::logic_error& e) {
//         EXPECT_EQ(e.what(), "wrong input!\n");
//     }
// }

TEST(HWFixture, outBoundstest) {
    int result = 12;
    int ten_flag;
    OutBounds(10, result, ten_flag);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(ten_flag, 1);

    result = 12;
    OutBounds(8, result, ten_flag);
    EXPECT_EQ(result, 4);
    EXPECT_EQ(ten_flag, 1);

    // TODO: negative test
}

TEST(HWFixture, same_sign_addTest) {
    std::string arg1 = "8ce";
    std::string arg2 = "eee";
    std::vector<int> num_vectors_1;
    bool positive_flag_1;
    StringToVector(arg1, 16, num_vectors_1, positive_flag_1);

    std::vector<int> num_vectors_2;
    bool positive_flag_2;
    StringToVector(arg2, 16, num_vectors_2, positive_flag_2);  

    std::vector<int> result;
    bool result_positive;
    same_sign_add(num_vectors_1, num_vectors_2, 16, result);
    EXPECT_EQ(result[0], 12);
    EXPECT_EQ(result[1], 11);
    EXPECT_EQ(result[2], 7);
    EXPECT_EQ(result[3], 1);
}

TEST(HWFixture, subtractionTest) {
    std::string arg1 = "8ce";
    std::string arg2 = "eee";
    std::vector<int> num_vectors_1;
    bool positive_flag_1;
    StringToVector(arg1, 16, num_vectors_1, positive_flag_1);

    std::vector<int> num_vectors_2;
    bool positive_flag_2;
    StringToVector(arg2, 16, num_vectors_2, positive_flag_2);  

    std::vector<int> result;
    bool result_positive;
    subtraction(num_vectors_2, num_vectors_1, 16, result);

    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 6);
}

TEST(HWFixture, additionTest) {
    std::string arg1 = "8ce";
    std::string arg2 = "-eee";
    std::vector<int> num_vectors_1;
    bool positive_flag_1{true}, positive_flag_2{true};
    StringToVector(arg1, 16, num_vectors_1, positive_flag_1);

    std::vector<int> num_vectors_2;
    StringToVector(arg2, 16, num_vectors_2, positive_flag_2);  

    std::vector<int> result;
    bool result_positive;
    bool result_flag;
    Addition(num_vectors_1, positive_flag_1, num_vectors_2, positive_flag_2, 16, result, result_flag);

    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 6);
    EXPECT_EQ(result_flag, 0);
}

TEST(HWFixture, additionTest2) {
    std::string arg1 = "+00000eee";
    std::string arg2 = "-eee";
    std::vector<int> num_vectors_1;
    bool positive_flag_1{true}, positive_flag_2{true};
    StringToVector(arg1, 16, num_vectors_1, positive_flag_1);

    std::vector<int> num_vectors_2;
    StringToVector(arg2, 16, num_vectors_2, positive_flag_2);  

    std::vector<int> result;
    bool result_positive;
    bool result_flag;
    Addition(num_vectors_1, positive_flag_1, num_vectors_2, positive_flag_2, 16, result, result_flag);

    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result_flag, 1);
}

TEST(HWFixture, additionTest3) {
    std::string arg1 = "+7";
    std::string arg2 = "-772";
    std::vector<int> num_vectors_1;
    bool positive_flag_1{true}, positive_flag_2{true};
    StringToVector(arg1, 8, num_vectors_1, positive_flag_1);

    std::vector<int> num_vectors_2;
    StringToVector(arg2, 8, num_vectors_2, positive_flag_2);  

    std::vector<int> result;
    bool result_positive;
    bool result_flag;
    Addition(num_vectors_1, positive_flag_1, num_vectors_2, positive_flag_2, 8, result, result_flag);

    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 6);
    EXPECT_EQ(result[2], 7);
    EXPECT_EQ(result_flag, 0);
}

TEST(HWFixture, isgreaterTest) {
    std::string a = "872";
    std::string b = "189";

    std::vector<int> v1, v2;
    bool p1, p2;
    StringToVector(a, 10, v1, p1);
    StringToVector(b, 10, v2, p2);
    EXPECT_EQ(IsGreater(v1, v2), 1);
}

TEST(HWFixture, convertMtoNTest) {
    std::string a = "123";

    std::vector<int> v1;
    bool p1, p2;
    StringToVector(a, 10, v1, p1);
    std::vector<int> result = ConvertMToN(v1, 10, 8);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 5);

}
TEST(HWtest, convertMtoNTest1) {
    std::string a = "7b";
    std::vector<int> v1;
    bool p1;
    StringToVector(a, 16, v1, p1);
    std::vector<int> result = ConvertMToN(v1, 16, 8);
    EXPECT_EQ(result[0], 7);
    EXPECT_EQ(result[1], 6);
    EXPECT_EQ(result[2], 2);
}
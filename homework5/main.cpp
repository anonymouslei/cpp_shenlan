#include <cassert>
#include <iostream>
#include <vector>

//基类是template, 子类不是template
template <typename T>
struct Matrix_dynamic {
  Matrix_dynamic() {
    row_ = 1;
    col_ = 1;
    elements_ = std::vector<T>();
  }

  Matrix_dynamic(int row, int col) : row_(row), col_(col) {
    for (int i = 0; i < row * col; ++i) {
      elements_.push_back(T{});
    }
  }

  int row_;
  int col_;
  std::vector<T> elements_;
};

template <typename T, int T_row, int T_col>
struct Matrix_static {
  Matrix_static() {
    elements_ = std::vector<T>();
    for (int i = 0; i < T_row * T_col; ++i) {
      elements_.push_back(T{});
    }
  }

private:
  std::vector<T> elements_;
};

template<typename T, int T_row = 0, int T_col = 0>
//struct Matrix : Matrix_dynamic<T> {
struct Matrix : std::conditional_t<T_row,
                                   Matrix_static<T, T_row, T_col>,
                                   Matrix_dynamic<T>> {
//template <typename T, int T_row, int T_col>
//struct Matrix : Matrix_static<T, T_row, T_col> {
//  Matrix() : std::conditional_t<T_row,
//                              Matrix_static<T, T_row, T_col>(),
//                                  Matrix_dynamic<T>()> {
//  }

  //TODO:
  Matrix(int row, int col) : {
  }

  Matrix<T> operator+(Matrix<T> &rhs) {
    if ((this->row_ == rhs.row_) && (this->col_ == rhs.col_)) {
      Matrix<T> matrix(this->row_, this->col_);
      auto size = this->elements_.size();
      for (int i = 0; i < size; ++i) {
        matrix.elements_.at(i) = this->elements_.at(i) + rhs.elements_.at(i);
      }
      return matrix;
    } else {
      throw std::logic_error("dimension is not equal\n");
    }
  };

  void print() const {
    int n = 1;
    for (const auto i : this->elements_) {
      std::cout << i << " ";
      if (n == this->col_) {
        std::cout << std::endl;
        n = 1;
      } else
        n++;
    }
    std::cout << std::endl;
  }
};

int main() {

  Matrix<int> a(2,2);
  a.print();
  Matrix<int> b(2, 2);
  Matrix<int> res = a+b;
  res.print();

  return 0;
}
#include <iostream>
#include <vector>

// the element of matix will be stored as array

template<typename T, int T_row, int T_col>
requires ((T_row > 0) && (T_col > 0))
struct Matrix {
  // constructor Matric<int, 2,3>
  Matrix() {
    elements_ = std::vector<T>();
    for (int i = 0; i < row_*col_; ++i) {
      elements_.push_back(T{});
    }
  }

  Matrix(std::initializer_list<T> l) : elements_(l) {
    elements_.resize(col_*row_);
  }

  // operator[][]
  typename std::vector<T>::iterator operator[](std::size_t idx) {
    return elements_.begin() + (idx * col_);
  }
  const typename std::vector<T>::iterator operator[](std::size_t idx) const {
    return elements_.begin() + (idx * col_);
  }

  // at
  T &at(std::size_t idx) {
    return elements_.at(idx);
  } // 可以使用 at 访问矩阵按行展开后对应的元素
  const T &at(std::size_t idx) const { return elements_.at(idx); }

  // reshape
  template <int C_row, int C_col>
  auto reshape() {
    Matrix<T, C_row, C_col> res;
    elements_.resize(C_col * C_row);
    for (int i = 0; i < C_row*C_col; ++i) {
      res.elements_.at(i) = elements_.at(i);
    }
    return res;
  }


  //add
  friend auto operator+(const Matrix &lhs, Matrix &rhs) {
    if ((lhs.row_ == rhs.row_) && (lhs.col_ == rhs.col_)) {
      Matrix matrix(lhs.row_, lhs.col_);
      auto size = lhs.elements_.size();
      for (int i = 0; i < size; ++i) {
        matrix.elements_.at(i) = lhs.elements_.at(i) + rhs.elements_.at(i);
      }
      return matrix;
    } else {
      throw std::logic_error("dimension is not equal\n");
    }
  };
  // -
  friend auto operator-(const Matrix<T, T_row, T_col> &lhs, const Matrix &rhs) {
    if ((lhs.row_ == rhs.row_) && (lhs.col_ == rhs.col_)) {
      Matrix matrix(lhs.row_, lhs.col_);
      auto size = lhs.elements_.size();
      for (int i = 0; i < size; ++i) {
        matrix.elements_.at(i) = lhs.elements_.at(i) - rhs.elements_.at(i);
      }
      return matrix;
    } else {
      throw std::logic_error("dimension is not equal\n");
    }
  }
  // *
  friend auto operator*(const Matrix &lhs, const Matrix &rhs) { //TODO: not finished
    if (lhs.col_ == rhs.row_) {
      Matrix matrix(lhs.row_, rhs.col_);
      for (int i = 0; i < lhs.row_ * rhs.col_; ++i) { // k
        for (int j = 0; j < lhs.row_; ++j) {          // i
          for (int k = 0; k < rhs.col_; ++k) {        // j
            matrix.at(i) = 1; // += lhs.elements_.at(j*lhs.col_+k) +
            // rhs.elements_.at(i*rhs.col_+k);
            // TODO:
          }
        }
      }
      std::cout << "debug 0" << std::endl;
      return matrix;
    } else {
      throw std::logic_error("dimension is not equal\n");
    }
  }

  void print() const {
    int n = 1;
    for (const auto i : elements_) {
      std::cout << i << " ";
      if (n == col_) {
        std::cout << std::endl;
        n = 1;
      } else
        n++;
    }
    std::cout << std::endl;
  }

  int row_ = T_row;
  int col_ = T_col;
  std::vector<T> elements_;
};

int main() {
  Matrix<int, 2, 3> mat1{1,2,3,4,5};
  Matrix<int, 3, 2> mat2{1,0,0,1};
//  Matrix<int, 2, 2> res = mat1*mat2;

  std::cout << "mat1: \n";
  mat1.print();
  Matrix<int, 3, 3> reshape_res = mat1.reshape<3,3>();
  std::cout << "reshape_res: \n";
  reshape_res.print();
}

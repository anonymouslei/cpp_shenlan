#include <iostream>
#include <vector>

template <typename T, int T_row, int T_col>
requires((T_row > 0) && (T_col > 0)) class Matrix {
public:
  Matrix() {
    elements_ = std::vector<T>();
    for (int i = 0; i < row_ * col_; ++i) {
      elements_.push_back(T{});
    }
  }

  Matrix(std::initializer_list<T> l) : elements_(l) {
    elements_.resize(col_ * row_);
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
  }
  const T &at(std::size_t idx) const { return elements_.at(idx); }

  // reshape
  template <int C_row, int C_col> auto reshape() {
    Matrix<T, C_row, C_col> res;
    elements_.resize(C_col * C_row);
    for (int i = 0; i < C_row * C_col; ++i) {
      res.at(i) = elements_.at(i);
    }
    return res;
  }

  // add
  template <int N_row, int N_col>
  Matrix<T, T_row, T_col> operator+(const Matrix<T, N_row, N_col> &rhs) {
    static_assert(T_col == N_col, "col is not equal");
    static_assert(T_row == N_row, "row is not equal");
    Matrix<T, T_row, T_col> matrix;
    auto size = this->elements_.size();
    for (int i = 0; i < size; ++i) {
      matrix.elements_.at(i) = this->elements_.at(i) + rhs.elements_.at(i);
    }
    return matrix;
  };
  // -
  template <int N_row, int N_col>
  Matrix<T, T_row, T_col> operator-(const Matrix<T, N_row, N_col> &rhs) {
    static_assert(T_col == N_col, "col is not equal");
    static_assert(T_row == N_row, "row is not equal");
    Matrix<T, T_row, T_col> matrix;
    auto size = this->elements_.size();
    for (int i = 0; i < size; ++i) {
      matrix.elements_.at(i) = this->elements_.at(i) - rhs.elements_.at(i);
    }
    return matrix;
  }
  // *
  template <int N_row, int N_col>
  Matrix<T, T_row, N_col> operator*(const Matrix<T, N_row, N_col> &rhs) {
    static_assert(T_col == N_row, "dimension is not satisfied");
    Matrix<T, T_row, N_col> matrix;
    for (int i = 0; i < this->row_ * N_col; ++i) { // k
      for (int j = 0; j < this->row_; ++j) {       // i
        for (int k = 0; k < N_col; ++k) {          // j
          matrix.at(i) = 1; // += lhs.elements_.at(j*lhs.col_+k) +
          // rhs.elements_.at(i*rhs.col_+k);
        }
      }
    }
    return matrix;
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

private:
  static constexpr size_t row_ = T_row; // use static constexpr
  static constexpr size_t col_ = T_col; // 索引应该为无符号数，所以用sdize_t
  std::vector<T> elements_;
};

// type 0: row, type 1: col
template <int Type, typename T, int T1_row, int T1_col, int T2_row, int T2_col>
Matrix<T, T1_row + T2_row *(1 - Type), T1_col + T2_col * Type>
concatenate(Matrix<T, T1_row, T1_col> mat1, Matrix<T, T2_row, T2_col> mat2) {
  if (!Type)
    static_assert(T1_col == T2_col, "col is not equal");
  else
    static_assert(T1_row == T2_row, "row is not equal");

  Matrix<T, T1_row + T2_row *(1 - Type), T1_col + T2_col * Type> matrix;
  int mat1_size = T1_row * T1_col;
  int mat2_size = T2_row * T2_col;
  for (int i = 0; i < mat1_size; ++i) {
    matrix.at(i) = mat1.at(i);
  }
  for (int i = 0; i < mat2_size; ++i) {
    matrix.at(i + mat1_size) = mat2.at(i);
  }
  return matrix;
}

int main() {
  Matrix<int, 2, 3> mat1{1, 2, 3, 4, 5};
  Matrix<int, 3, 2> mat2{1, 0, 0, 1};
  Matrix<int, 2, 2> res = mat1 * mat2;
  res.print();
  res = res + res;
  res.print();
  res = res - res;
  res.print();

  std::cout << "mat1: \n";
  mat1.print();
  Matrix<int, 3, 3> reshape_res = mat1.reshape<3, 3>();
  std::cout << "reshape_res: \n";
  reshape_res.print();

  Matrix<int, 2, 2> mat4;
  Matrix<int, 2, 2> mat5;
  Matrix<int, 3, 3> mat6;
  Matrix<int, 4, 2> res1 = concatenate<0>(mat4, mat5);
  res1.print();
  //  concatenate<1>(mat4, mat6);
}

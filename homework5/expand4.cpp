#include <cassert>
#include <concepts>
#include <vector>
#include <iostream>
// using fun template

template <typename T>
concept IsAvail =
!std::is_pointer_v<T> || !std::is_void_v<T> || !std::is_reference_v<T>;

template <typename T> concept Addable = requires(T a, T b) { a + b; };
template <typename T> concept Mulable = requires(T a, T b) { a *b; };
template <typename T> concept Subable = requires(T a, T b) { a - b; };

template <IsAvail T> class Matrix_dynamic {
public:
  Matrix_dynamic() {
    row_ = 1;
    col_ = 1;
    elements_ = std::vector<T>();
  }

  Matrix_dynamic(const Matrix_dynamic &x)
      : row_(x.row_), col_(x.col_), elements_(x.elements_) {}

  Matrix_dynamic(Matrix_dynamic &&x) noexcept
      : row_(x.row_), col_(x.col_), elements_(x.elements_){};

  Matrix_dynamic(int row, int col) : row_(row), col_(col) {
    for (int i = 0; i < row * col; ++i) {
      elements_.push_back(T{});
    }
  }

  Matrix_dynamic(std::initializer_list<T> l) : elements_(l) {
    //     ref: cppreference initializer_list
    col_ = 1;
    row_ = elements_.size();
  }
  //  operator []
  typename std::vector<T>::iterator operator[](std::size_t idx) {
    return elements_.begin() + (idx * col_);
  }
  const typename std::vector<T>::iterator operator[](std::size_t idx) const {
    return elements_.begin() + (idx * col_);
  }

  T &at(std::size_t idx) {
    return elements_.at(idx);
  } // 可以使用 at 访问矩阵按行展开后对应的元素
  const T &at(std::size_t idx) const { return elements_.at(idx); }

  void push_back(T item) { elements_.emplace_back(item); };
  void reshape(int row, int column) {
    elements_.resize(row * column);
    row_ = row;
    col_ = column;
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

  // Subtraction()
  friend auto operator-(const Matrix_dynamic &lhs, const Matrix_dynamic &rhs) {
    static_assert(Subable<T>, "is not sub able");
    if ((lhs.row_ == rhs.row_) && (lhs.col_ == rhs.col_)) {
      Matrix_dynamic matrix(lhs.row_, lhs.col_);
      auto size = lhs.elements_.size();
      for (int i = 0; i < size; ++i) {
        matrix.elements_.at(i) = lhs.elements_.at(i) - rhs.elements_.at(i);
      }
      return matrix;
    } else {
      throw std::logic_error("dimension is not equal\n");
    }
  }
  // mul
  friend auto operator*(const Matrix_dynamic &lhs, const Matrix_dynamic &rhs) {
    static_assert(Mulable<T>, "is not mul able");
    if (lhs.col_ == rhs.row_) {
      Matrix_dynamic matrix(lhs.row_, rhs.col_);
      for (int i = 0; i < lhs.row_ * rhs.col_; ++i) {
        for (int j = 0; j < lhs.row_; ++j) {
          for (int k = 0; k < rhs.col_; ++k) {
            matrix.at(i) = 1; // += lhs.elements_.at(j*lhs.col_+k) +
                              // rhs.elements_.at(i*rhs.col_+k);
          }
        }
      }
      std::cout << "debug 0" << std::endl;
      return matrix;
    } else {
      throw std::logic_error("dimension is not equal\n");
    }
  }

  int get_row() const {
    return row_;
  }
  int get_col() const {
    return col_;
  }

private:
  int row_;
  int col_;
  std::vector<T> elements_;
};


template <typename T, int T_row, int T_col>
requires((T_row > 0) && (T_col > 0)) class Matrix_static {
public:
  Matrix_static() {
    elements_ = std::vector<T>();
    for (int i = 0; i < row_ * col_; ++i) {
      elements_.push_back(T{});
    }
  }

  Matrix_static(int row, int col) : row_(row), col_(col) {
    for (int i = 0; i < row * col; ++i) {
      elements_.push_back(T{});
    }
  }

  Matrix_static(std::initializer_list<T> l) : elements_(l) {
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
    Matrix_static<T, C_row, C_col> res;
    elements_.resize(C_col * C_row);
    for (int i = 0; i < C_row * C_col; ++i) {
      res.at(i) = elements_.at(i);
    }
    return res;
  }

  // -
  template <int N_row, int N_col>
  Matrix_static<T, T_row, T_col> operator-(const Matrix_static<T, N_row, N_col> &rhs) {
    static_assert(T_col == N_col, "col is not equal");
    static_assert(T_row == N_row, "row is not equal");
    Matrix_static matrix(this->row_, this->col_);
    auto size = this->elements_.size();
    for (int i = 0; i < size; ++i) {
      matrix.elements_.at(i) = this->elements_.at(i) - rhs.elements_.at(i);
    }
    return matrix;
  }
  // *
  template <int N_row, int N_col>
  Matrix_static<T, T_row, N_col> operator*(const Matrix_static<T, N_row, N_col> &rhs) {
    static_assert(T_col == N_row, "dimension is not satisfied");
    Matrix_static<T, T_row, N_col> matrix(T_row, N_col);
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
  int get_row() const {
    return row_;
  }
  int get_col() const {
    return col_;
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
  int row_ = T_row;
  int col_ = T_col;
  std::vector<T> elements_;
};

template <typename L, typename R>
auto operator+(const L& lhs, const R& rhs) {
  L res(lhs.get_row(), rhs.get_col());
  auto size = lhs.get_row() * lhs.get_col();
  for (int i = 0; i < size; ++i) {
    res.at(i) = lhs.at(i) + rhs.at(i);
  }
  return res;
}

int main() {
  Matrix_static<int, 2, 3> mat1{1, 2, 3, 4, 5};
  Matrix_static<int, 3, 2> mat2{1, 0, 0, 1};
//  Matrix_static<int, 2, 2> res = mat1 + mat2;
//  res.print();
  mat2.print();
  mat2 = mat2 + mat2;
  mat2.print();

  Matrix_dynamic<int> matrix(2, 3);
  Matrix_dynamic<int> res_dyna = matrix + matrix;
  res_dyna.print();
}
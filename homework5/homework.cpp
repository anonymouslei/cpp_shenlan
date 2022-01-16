#include <initializer_list>
#include <iostream>
#include <vector>
#include <cassert>
#include <memory>

template<typename T>
concept IsAvail = !std::is_pointer_v<T> ||
                  !std::is_void_v<T> ||
                  !std::is_reference_v<T>;

template<typename T>
concept Addable = requires (T a) {
    a + a;
};

template <IsAvail T>
class Matrix {
public:
  Matrix() {
    row_ = 1;
    col_ = 1;
    elements_ = std::vector<T>();
  }

    Matrix(const Matrix& x): row_(x.row_), col_(x.col_),
    elements_(x.elements_) {
      std::cout << "copy constructor\n";
    }

    Matrix(Matrix&& x) noexcept : row_(x.row_), col_(x.col_),
    elements_(x.elements_) { std::cout << "move constructor\n";
                                                              };

  Matrix(int row, int col) : row_(row), col_(col) {
    for (int i = 0; i < row * col; ++i) {
      elements_.push_back(T{});
    }
  }

  Matrix(std::initializer_list<T> l) : elements_(l) {
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
  //因为存在at和Push_back这两个函数，证明我们在存储matrix的元素的时候也应该是按行展开进行的存储
  void reshape(int row,
               int column) // 可以使用 reshape()修改矩阵尺寸，
                           // 多余的元素会被删除， 缺少的元素会使用默认值填充
  {
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

  // add()
  friend auto operator+(const Matrix<T> &lhs, Matrix<T> &rhs) {
    if ((lhs.row_ == rhs.row_) && (lhs.col_ == rhs.col_)) {
      Matrix<T> matrix(lhs.row_, lhs.col_);
      auto size = lhs.elements_.size();
      for (int i = 0; i < size; ++i) {
        matrix.elements_.at(i) = lhs.elements_.at(i) + rhs.elements_.at(i);
      }
      return matrix;
    } else {
      throw std::logic_error("dimension is not equal\n");
    }
  };
  // Subtraction()
  friend auto operator-(const Matrix &lhs, const Matrix &rhs) {
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
  // mul
  friend auto operator*(const Matrix &lhs, const Matrix &rhs) {
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

  //需要满足std::move
  std::vector<T> elements_;

private:
  int row_;
  int col_;
};

// template<typename T>
// requires Addable<T>
// T operator+(const T& lhs, T& rhs) {
//   std::cout << "outside add\n";
//   return lhs + rhs;
//}

int main() {
  Matrix<int> matrix(2, 3);
  Matrix<int> mat1;
  Matrix<int> mat2(2, 2);
  //  matrix.col_ = 3;
  //  matrix.row_ = 2;
  matrix.elements_.push_back(1);
  matrix.elements_.push_back(2);
  matrix.elements_.push_back(3);
  matrix.elements_.push_back(4);
  std::cout << matrix[1][0] << std::endl;
  matrix[1][0] = 8;
  std::cout << matrix[1][0] << std::endl;

  mat2[1][0] = 42;
  assert(mat2.at(2) == 42);
  mat2.at(1) = 1;

  mat2.push_back(13);
  mat2.push_back(14);
  assert(mat2.at(4) == 13);
  assert(mat2.at(5) == 14);

  mat2.reshape(3, 3);
  std::cout << "mat2: \n";
  mat2.print();

  Matrix<int> mat3{1, 2, 3, 4};
  Matrix<int> mat4{5, 6, 7, 8};
  mat3.reshape(2, 3);
  mat4.reshape(3, 2);
  std::cout << "mat3: \n";
  mat3.print();
  mat4.print();

    Matrix<int> mat_res = mat3 + mat3;
    std::cout << "mat_res: \n";
    mat_res.print();

  Matrix<int> mat_res_mul = mat3 * mat4;
  std::cout << "mat_res_mul: \n";
  mat_res_mul.print();

//  struct AddOnly {
//    int v;
//    AddOnly operator + (AddOnly& rop) {
//      return AddOnly{v + rop.v};
//    }
//  };
//  Matrix<AddOnly> mat;
//  mat + mat;
  //    Matrix<int> mat_move = std::move(mat3);
  //    std::cout << "mat move: \n";
  //    mat_move.print();

  return 0;
}

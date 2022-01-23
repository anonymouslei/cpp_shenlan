// using inherit template

#include <initializer_list>
#include <iostream>
#include <vector>

// base class is template, derived class is not template
// 第一层基类只有数据成员，保存矩阵数据。有两种基类，一种是静态内存分配，一种是动态内存分配
template <typename T> struct MatrixDynamicData {
  size_t row_=1;
  size_t col_;
  std::vector<T> elements_;
};

template <typename T, size_t T_row, size_t T_col> struct MatrixStaticData {
  MatrixStaticData() {
    elements_ = std::vector<T>();
    for (int i = 0; i < row_ * col_; ++i) {
      elements_.push_back(T{});
    }
  }

  static constexpr size_t row_ = T_row;
  static constexpr size_t col_ = T_col;
  std::vector<T> elements_;
};

//和我的作业相比，这个使用了三层继承的方法。将所有的加法等实现都放到了MatrixBase这个基类
//他并不是一个template,而是根据不同的情况来继承不同的data基类
//这个方法解决了我的程序在需要新建resultMatrix,不知道应该如何选择相对应的初始化函数的缺点。
template <typename T> struct MatrixBase : public T {

  template <typename T1> void initializer(std::initializer_list<T1> l) {
    auto ptr = l.begin();
    for (size_t i = 0; i < l.size(); i++) {
      T::elements_.at(i) = *(ptr);
      ptr++;
    }
  }

  void set_col(const size_t n) {
    T::col_ = n;
  }

  void set_row(const size_t n) {
    T::row_ = n;
  }

  int get_col() const {
    return T::col_;
  }

  int get_row() const {
    return T::row_;
  }

  template <class T1, class T2>
  void add(const T1 &rhs, T2 &res) {
    for (size_t i = 0; i < T::row_ * T::col_; ++i)
    {
      res.elements_[i] = T::elements_.at(i) + rhs.elements_.at(i);
    }
  }

  template <class T1, class T2>
  void mul(const T1& rhs, T2& res) {
    for(size_t i = 0; i< res.row_ * res.col_; ++i) {
//  for(size_t i = 0; i< T2::row_ * T2::ol_; ++i) { // 会报invalid use of non-static的错误
      res.elements_.at(i) = 1;
    }
  }

  void reshape(size_t row, size_t column) {
    T::elements_.resize(row * column);
    T::row_ = row;
    T::col_ = column;
  }

  void print() const {
    int n = 1;
    for (const auto i : T::elements_) {
      std::cout << i << " ";
      if (n == T::col_) {
        std::cout << std::endl;
        n = 1;
      } else
        n++;
    }
    std::cout << std::endl;
  }
};

// 子类根据情况来选择继承哪个基类。用特化的方法来决定继承哪个子类。
template <typename T, size_t... sizes> struct Matrix;

template <typename T>
struct Matrix<T> : public MatrixBase<MatrixDynamicData<T>> {

  Matrix() {};

  Matrix(const size_t row, const size_t col) {
    this->set_row(row);
    this->set_col(col);
    this->reshape(row, col);
  }

  Matrix(std::initializer_list<T> l) {
    this->reshape(1, l.size());
    this->initializer(l);
    this->set_col(l.size());
    this->set_row(1);
  }

  Matrix operator+(const Matrix &rhs) {
    Matrix res(this->get_row(), this->get_col());
    // 还需要保证res尺寸正确，rhs尺寸正确，否则抛出异常
    this->add(rhs, res);
    return res;
  }

  Matrix operator*(const Matrix &rhs) {
    Matrix res(this->get_row(), rhs.get_col());
    this->mul(rhs, res);
    return res;
  }

};

template <typename T, size_t T_row, size_t T_col>
struct Matrix<T, T_row, T_col>
    : public MatrixBase<MatrixStaticData<T, T_row, T_col>> {
  Matrix() {};
  Matrix(std::initializer_list<T> l) { this->initializer(l); }

  Matrix operator+(const Matrix &rhs) {
    Matrix res;
    // 还需要保证res尺寸正确，rhs尺寸正确，否则抛出异常
    this->add(rhs, res);
    return res;
  }

  template <size_t N_row, size_t N_col>
  Matrix<T, T_row, N_col> operator*(const Matrix<T, N_row, N_col> &rhs)
  {
    Matrix<T, T_row, N_col> res;
    this->mul(rhs, res);
    return res;
  }
};

int main() {
  Matrix<int, 2, 3> mat1{1, 2, 3, 4, 5};
  Matrix<int, 3, 2> mat2{1, 0, 0, 1};
  //  Matrix_static<int, 2, 2> res = mat1 + mat2;
  mat2.print();
//  mat2 = mat2 + mat2;
//  mat2.print();
  Matrix<int, 2, 2> res_static = mat1 * mat2;
  res_static.print();

  Matrix<int> mat3{1, 2, 3, 4};
  Matrix<int> res_dyna = mat3 + mat3;
  res_dyna.print();
  Matrix<int> mat4(2,3);
  Matrix<int> mat5(3,2);
  Matrix<int> res_mul_dyna = mat4 * mat5;
  res_mul_dyna.print();
}
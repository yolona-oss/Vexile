#ifndef MATRIX_H_J2PRSDIL
#define MATRIX_H_J2PRSDIL

#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <string>

namespace Vexile {

template <typename T>
auto defaultMatrixFillFunction = [](int r, int c, T) {
  if (r - c == 0) {
    return 1;
  } else {
    return 0;
  }
};

// NOTE create matrixbase which contain base matrix orientation methods
// and cover matrixbase with class contains matrix operations
//
// NOTE all methods no throw, but assert :)
// i must switch it to throw next time, its my old implementation
//
// TODO think about throws in methods,
// a lot of them use throw and throw only a C-style string
template <typename T> class Matrix {
public:
  // applyFunc return new cell value
  // NOTE maybe use T& for change matrix cell value?
  using applyFunc = std::function<T(int curr, int curc, T)>;
  using applyByValueOnlyFunc = std::function<T(T)>;

  // 2x2
  Matrix();
  // quad matrix
  Matrix(int rowCol, applyFunc fillFunction = defaultMatrixFillFunction<T>);
  Matrix(int row, int col, applyFunc fillFunction = defaultMatrixFillFunction<T>);
  Matrix(const std::initializer_list<const std::initializer_list<T>> &Tlist);
  Matrix(const Matrix<T> &other);
  virtual ~Matrix();

  const T *raw() const;

  // matrix exponentiation
  Matrix<T> getPowerOf(int d) const;

  // apply to this
  virtual Matrix<T> &transpose();
  // return new matrix
  virtual Matrix<T> getTransposition() const;
  T minor(int r, int c) const;
  T cofactor(int r, int c) const;
  // Matrix<T>&        toTriangle();
  // Matrix<T>         getTriangle() const;
  T determinant() const;

  void apply(applyFunc);
  void apply(applyByValueOnlyFunc);

  // get matrix cell in certain position from Zero
  virtual T &operator()(int row, int col);
  virtual T &operator()(int row, int col) const;

  // get by absolute position
  T &operator[](const int ind);
  T &operator[](const int ind) const;

  Matrix<T> &operator=(const Matrix<T> &other);

  bool isQuad() const;
  int cellsCount() const;

  int rows() const;
  int cols() const;

protected:
  int maxNulFactorRow() const;
  Matrix(const T *, int rows, int cols);

  mutable int _rows;
  mutable int _cols;

  // NOTE mb unique_ptr?
  T *_matrix;
};

template <typename T> std::ostream &operator<<(std::ostream &out, const Matrix<T> &v);

template <typename T> Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2);
template <typename T> Matrix<T> operator-(const Matrix<T> &m1, const Matrix<T> &m2);
template <typename T> Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2);
template <typename T> Matrix<T> operator*(const Matrix<T> &m1, const T &val);
template <typename T> bool operator==(const Matrix<T> &m1, const Matrix<T> &m2);
template <typename T> bool operator!=(const Matrix<T> &m1, const Matrix<T> &m2);

#include "Vexile/Core/Math/Matrix.inl"

typedef Matrix<float> Matrixf;
typedef Matrix<int> Matrixi;
typedef Matrix<unsigned int> Matrixu;

} // namespace Vexile

#endif /* end of include guard: MATRIX_H_J2PRSDIL */

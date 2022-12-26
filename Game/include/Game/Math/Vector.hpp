#pragma once

#include "Vexile/Core/Math/Matrix.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace Vexile {

template <typename T> class Vector : public Matrix<T> {
public:
  Vector(); // 2x1
  Vector(const int co);
  Vector(const std::initializer_list<T> &Tlist);
  Vector(const Vector<T> &other);
  virtual ~Vector();

  virtual T &operator()(int const &i) override;
  virtual T &operator()(int const &i) const override;

  Vector<T> &operator=(const Vector<T> &rhs);

  Vector<T> getNormalized() const;
  T magnitude() const;
  T dotProduct(Vector<T> &s) const; //скалярное произведение
  T projection(Vector<T> &s) const;
  void truncate(T val);
  Vector<T> getTruncated(T val) const;

  const size_t size;

private:
  using Matrix<T>::cols;
  using Matrix<T>::rows;

  // hide
  // using Matrix<T>::operator();
  using Matrix<T>::cofactor;
  using Matrix<T>::determinant;
  using Matrix<T>::minor;
  using Matrix<T>::maxNulFactorRow;
  using Matrix<T>::getTransposition;
  using Matrix<T>::transpose;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &v);

template <typename T>
Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2);
template <typename T>
Vector<T> operator-(const Vector<T> &v1, const Vector<T> &v2);
template <typename T> Vector<T> operator*(const Vector<T> &v1, const T &val);
template <typename T>
Vector<T> operator*(const Vector<T> &v1, const Matrix<T> &m1);
template <typename T>
Vector<T> operator*(const Matrix<T> &m1, const Vector<T> &v1);

template <typename T, int len = 2> class Vectorl final : Vector<T> {
public:
  Vectorl();
  Vectorl(const std::initializer_list<T> &Tlist);

private:
};

template <typename T> struct Vector2 {
  Vector2() : x(0), y(0) {}
  Vector2(T x, T y) : x(x), y(y) {}
  T x;
  T y;
};

template <typename T>
Vector2<T> operator+(const Vector2<T> &v1, const Vector2<T> &v2);
template <typename T>
Vector2<T> operator-(const Vector2<T> &v1, const Vector2<T> &v2);
template <typename T> Vector2<T> operator*(const Vector2<T> &v1, const T &val);
template <typename T> Vector2<T> operator/(const Vector2<T> &v1, const T &val);

#include "Vexile/Core/Math/Vector.inl"

typedef Vector<int> Vectori;
typedef Vector<unsigned> Vectoru;
typedef Vector<float> Vectorf;

typedef Vector2<int> Vector2i;
typedef Vector2<unsigned> Vector2u;
typedef Vector2<float> Vector2f;

} // namespace Vexile

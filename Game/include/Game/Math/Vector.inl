template <typename T> Vector<T>::Vector() : Vector(2) {}

template <typename T>
Vector<T>::Vector(const int i) : Matrix<T>::Matrix(1, i), size(i) {
  for (int i = 0; i < this->size; ++i) {
    this->m_matrix[i] = 0;
  }
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> &Tlist)
    : Vector(Tlist.size()) {
  auto it = Tlist.begin();
  for (int l_i = 0; l_i < this->size; l_i++, it++) {
    this->m_matrix[l_i] = *it;
  }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &copy)
    : Matrix<T>::Matrix(copy), size(copy.size) {}

template <typename T> Vector<T>::~Vector() {}

template <typename T> Vector<T> Vector<T>::getNormalized() const {
  int mg = this->magnitude();
  Vector<T> ret(this->size);
  for (int i = 0; i < this->size; ++i) {
    ret(i) = ret(i) / mg;
  }
  return ret;
}

template <typename T> T Vector<T>::magnitude() const {
  T sum = 0;
  if (this->size == 2) {
    sum = this->m_matrix[0] * this->m_matrix[0] +
          this->m_matrix[1] * this->m_matrix[1];
  } else if (this->size == 3) {
    sum = this->m_matrix[0] * this->m_matrix[0] +
          this->m_matrix[1] * this->m_matrix[1] +
          this->m_matrix[2] * this->m_matrix[2];
  } else {
    for (int i = 0; i < this->size; ++i) {
      sum += this->m_matrix[i] * this->m_matrix[i];
    }
  }
  return sqrt(sum);
}

//скалярное произведение
template <typename T> T Vector<T>::dotProduct(Vector<T> &s) const {
  assert(this->size == s.size);
  T ret = 0;
  if (this->size == 2) {
    ret = this->m_matrix[0] * s(0) + this->m_matrix[1] * s(1);
  } else if (this->size == 3) {
    ret = this->m_matrix[0] * s(0) + this->m_matrix[1] * s(1) +
          this->m_matrix[2] * s(2);
  } else {
    for (int i = 0; i < this->size; ++i) {
      ret += this->m_matrix[i] * s(i);
    }
  }

  return ret;
}

// get projcetion of vector
template <typename T> T Vector<T>::projection(Vector<T> &v) const {
  assert(v.size == this->size);
  return dotProduct(v.getNormalize());
}

// get truncated vector
template <typename T> void Vector<T>::truncate(T val) {
  if (magnitude() > val) {
    return this->getNormalize() * val;
  }
}

// get truncated vector
template <typename T> Vector<T> Vector<T>::getTruncated(T val) const {
  auto ret = this;
  return ret.trancate();
}

//////////////////////////////////////////////////////////////

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
  assert(rhs.size == this->size);
  if (this != &rhs) {
    for (int i = 0; i < this->size; ++i) {
      this->m_matrix[i] = rhs[i];
    }
  }
  return *this;
}

template <typename T> T &Vector<T>::operator()(int const &i) {
  assert(i <= this->size);
  return this->m_matrix[i];
}

template <typename T> T &Vector<T>::operator()(int const &i) const {
  assert(i <= this->size);
  return this->m_matrix[i];
}

template <typename T>
Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2) {
  assert(v1.size == v2.size);
  Vector<T> ret(v1.size);
  for (int i = 0; i < ret.size; ++i) {
    ret(i) = v1(i) + v2(i);
  }
  return ret;
}

template <typename T>
Vector<T> operator-(const Vector<T> &v1, const Vector<T> &v2) {
  assert(v1.size == v2.size);
  Vector<T> ret(v1.size);
  for (int i = 0; i < ret.size; ++i) {
    ret(i) = v1(i) - v2(i);
  }
  return ret;
}

template <typename T> Vector<T> operator*(const Vector<T> &v1, const T &val) {
  Vector<T> ret(v1.size);
  for (int i = 0; i < v1.size; ++i) {
    ret(i) = v1(i) * val;
  }
  return ret;
}

template <typename T>
Vector<T> operator*(const Vector<T> &v1, const Matrix<T> &m1) {
  assert(v1.size == m1.cols);
  T sum;
  Vector<T> ret(v1.size);
  for (int row = 0; row < m1.rows; ++row) {
    sum = 0;
    for (int col = 0; col < m1.cols; ++col) {
      sum += m1(row, col) * v1(col);
    }
    ret(row) = sum;
  }
  return ret;
}

template <typename T>
Vector<T> operator*(const Matrix<T> &m1, const Vector<T> &v1) {
  assert(v1.size == m1.cols);
  T sum;
  Vector<T> ret(v1.size);
  for (int row = 0; row < m1.rows; ++row) {
    sum = 0;
    for (int col = 0; col < m1.cols; ++col) {
      sum += m1(row, col) * v1(col);
    }
    ret(row) = sum;
  }
  return ret;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &v) {
  out << "Vector";
  /* out << " of " << type_name<decltype((ci))>() << " "; */

  out << "{";
  for (int i = 0; i < v.size; ++i) {
    out << v(i);
    if (i != v.size - 1) {
      out << ", ";
    }
  }
  out << "}";

  return out;
}

//////////////////////////////////////////////////////////////

template <typename T, int len>
Vectorl<T, len>::Vectorl() : Vector<T>::Vector(len) {}

template <typename T, int len>
Vectorl<T, len>::Vectorl(const std::initializer_list<T> &Tlist)
    : Vector<T>::Vector(Tlist) {
  assert(len == Tlist.size());
}

//////////////////////////////////////////////////////

template <typename T>
Vector2<T> operator+(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>({v1.x + v2.x, v1.y + v2.y});
}

template <typename T>
Vector2<T> operator-(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>({v1.x - v2.x, v1.y - v2.y});
}

template <typename T> Vector2<T> operator*(const Vector2<T> &v1, const T &val) {
  return Vector2<T>({v1.x * val, v1.y * val});
}

template <typename T> Vector2<T> operator/(const Vector2<T> &v1, const T &val) {
  return Vector2<T>({v1.x / val, v1.y / val});
}

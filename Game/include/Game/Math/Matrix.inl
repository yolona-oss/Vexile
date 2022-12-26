// 2x2
template <typename T> Matrix<T>::Matrix() : Matrix(2, 2) {}

template <typename T>
Matrix<T>::Matrix(const T *mtx, int row, int col)
    : _matrix(new T[row * col]), _rows(row), _cols(col) {
  int i = 0;
  while (*mtx++) {
    _matrix[i++] = *mtx;
  }

  if (i != row * col) {
    delete[] _matrix;
    throw "Error: passed matrix array not matches row and col parameters";
  }
}

template <typename T>
Matrix<T>::Matrix(int r, int c, applyFunc fillFunc)
    : _rows(r), _cols(c), _matrix(new T[this->_rows * this->_cols]) {
  if (!(r > 0 && c > 0)) {
    delete[] _matrix;
    throw "Error: invalid matrix depth propery passed. Rows and Cols must be "
          "positive non zero values";
  }
  if (!(this->_rows > 0 && this->_cols > 0)) {
    throw "Error: Cannot copy matrix with not positive row and col value";
  }
  apply(fillFunc);
}

template <typename T>
Matrix<T>::Matrix(int rowCol, applyFunc fill) : Matrix(rowCol, rowCol, fill) {}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
    : _cols(other._cols), _rows(other._rows), _matrix(new T[this->_cols * this->_rows]) {
  if (!(this->_rows > 0 && this->_cols > 0)) {
    throw "Error: Cannot copy matrix with not positive row and col value";
  }

  // std::copy?????????????
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      this->_matrix[i * _cols + j] = other(i, j);
      /* this->_matrix[i * _cols + j] = other[i * other._cols + j]; */
    }
  }
}

// its ok?
template <typename T>
Matrix<T>::Matrix(const std::initializer_list<const std::initializer_list<T>> &Tlist)
    : Matrix(Tlist.size(), Tlist.begin()->size()) {

  /* for (auto& x : Tlist) */
  /*     assert(x.size() > this->_cols); */
  auto it = Tlist.begin(); // iterate through outer list
  for (int l_r = 0; l_r < this->_rows; l_r++, it++) {
    auto inIt = it->begin(); // iterate through inner list
    for (int l_c = 0; l_c < this->_cols; ++l_c, ++inIt) {
      _matrix[l_r * this->_cols + l_c] = *inIt;
    }
  }
}

template <typename T> Matrix<T>::~Matrix() { delete _matrix; }

template <typename T> const T *Matrix<T>::raw() const { return _matrix; }

template <typename T> int Matrix<T>::rows() const { return _rows; }
template <typename T> int Matrix<T>::cols() const { return _cols; }

template <typename T> int Matrix<T>::cellsCount() const { return _cols * _rows; }

template <typename T> void Matrix<T>::apply(applyFunc f) {
  for (int i = 0; i < cellsCount(); i++) {
    const int row = i / _rows;
    const int col = i - row * _cols;
    _matrix[i] = f(row, col, _matrix[i]);
  }
}

// maybe use as decorator to general apply() with aplyFunc?
template <typename T> void Matrix<T>::apply(applyByValueOnlyFunc f) {
  for (int i = 0; i < cellsCount(); i++) {
    _matrix[i] = f(_matrix[i]);
  }
}

template <typename T> bool Matrix<T>::isQuad() const { return this->_cols == this->_rows; }

template <typename T> Matrix<T> Matrix<T>::getPowerOf(int d) const {
  if (!isQuad()) {
    throw "Error: Canot get exponentiation of not quad matrix";
  }
  Matrix<T> ret(*this);
  while (--d > 0) {
    ret = ret * (*this);
  }
  return ret;
}

template <typename T> Matrix<T> Matrix<T>::getTransposition() const {
  if (!isQuad()) {
    throw "Error: Cannot get transposition of not quad matrix";
  }

  Matrix<T> ret(3, 3);
  for (int r = 0; r < ret._rows; r++) {
    for (int c = 0; c < ret._cols; c++) {
      for (int i = 0; i < ret._rows; i++) {
        ret(r, c) = _matrix[c * _cols + r];
      }
    }
  }

  return ret;
}

template <typename T> Matrix<T> &Matrix<T>::transpose() {
  for (int r = 0; r < _rows; r++) {
    for (int c = 0; c < _cols; c++) {
      for (int i = 0; i < _rows; i++) {
        this->_matrix[r * _cols + c] = this->_matrix[c * _cols + r];
      }
    }
  }
  return *this;
}

template <typename T> T Matrix<T>::minor(int row, int col) const {
  Matrix<T> mtx(_rows - 1, _cols - 1);
  int inner_row = 0, inner_col = 0;

  for (int mtx_row = 0; mtx_row < this->_rows; mtx_row++) {
    if (mtx_row != row) {
      inner_col = 0;
      for (int mtx_col = 0; mtx_col < _cols; mtx_col++) {
        if (mtx_col != col) {
          mtx(inner_row, inner_col) = _matrix[mtx_row * _cols + mtx_col];
          inner_col++;
        }
      }
      inner_row++;
    }
  }

  return mtx.determinant();
}

template <typename T> T Matrix<T>::cofactor(int row, int col) const {
  T cofactor = minor(row, col);

  return ((row + col) % 2 == 0) ? cofactor : -cofactor;
}

/* template<typename T> */
/* void Matrix<T>::toTriangle() */
/* { */
/*     T l_mul; */
/*     for (int l_line = 0; l_line < (_rows - 1); l_line++) { */
/*         for (int l_row = 0; l_row < (_rows - 1); l_row++) { */
/*             l_mul = -1 * (this->_matrix[(l_row + 1) * _cols + l_line] / */
/*                     this->_matrix[l_line * _cols + l_line]); */
/*             for (int l_col = 0; l_col < _cols; l_col++) { */
/*                 this->_matrix[(l_row + 1) * _cols + l_col] =
 * this->_matrix[(l_row + 1) * _cols + l_col] + */
/*                     this->_matrix[l_line * _cols + l_col] * l_mul; */
/*             } */
/*         } */
/*     } */
/* } */

/* template<typename T> */
/* Matrix<T> Matrix<T>::getTriangle() const */
/* { */
/*     Matrix<T> ret(*this); */
/*     ret.toTriangl(); */
/*     return ret; */
/* } */

template <typename T> T Matrix<T>::determinant() const {
  T det = 0;

  if (isQuad()) {
    switch (_rows) {
    case 1: {
      throw "Determinant unexists for 1x1 matrix";
      break;
    }
    /* 2x2 */
    case 2:
      det = _matrix[0] * _matrix[3] - _matrix[1] * _matrix[2];
      break;

    /* 3x3 */
    case 3:
      det = (_matrix[0] * _matrix[4] * _matrix[8] + _matrix[3] * _matrix[7] * _matrix[2] +
             _matrix[1] * _matrix[5] * _matrix[6]) -
            (_matrix[2] * _matrix[4] * _matrix[6] + _matrix[1] * _matrix[3] * _matrix[8] +
             _matrix[0] * _matrix[5] * _matrix[7]);
      break;

    /* higer */
    default: {
      int nulFactorRow = this->maxNulFactorRow();
      for (int col = 0; col < _cols; col++) {
        det += _matrix[nulFactorRow * _cols + col] * this->cofactor(nulFactorRow, col);
      }
      break;
    }
    }
  }

  return det;
}

template <typename T> int Matrix<T>::maxNulFactorRow() const {
  int l_max, l_cur, ret;
  ret = l_max = 0;

  for (int l_row = 0; l_row < _rows; l_row++) {
    l_cur = 0;
    for (int l_col = 0; l_col < _cols; l_col++) {
      if (_matrix[l_row * _cols + l_col] == 0) {
        l_cur++;
      }
    }
    if (l_cur > l_max) {
      l_max = l_cur;
      ret = l_row;
    }
  }

  return ret;
}

template <typename T> Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2) {
  if (!(m1.cols() == m2.cols() && m1.rows() == m2.rows())) {
    throw "Error: cannot calculate matrix sum with different matrix size";
  }
  /* add check for eq r1, r2; c1, c2 */
  Matrix<T> ret(m1.rows(), m1.cols());
  for (int row = 0; row < m1.rows(); row++) {
    for (int col = 0; col < m1.cols(); col++) {
      ret(row, col) = m1(row, col) + m2(row, col);
    }
  }
  return ret;
}

template <typename T> Matrix<T> operator-(const Matrix<T> &m1, const Matrix<T> &m2) {
  if (!(m1.cols() == m2.cols() && m1.rows() == m2.rows())) {
    throw "Error: cannot calculate matrix substruct with different matrix size";
  }

  Matrix<T> ret(m1.rows(), m1.cols());
  for (int i = 0; i < m1.rows(); i++) {
    for (int j = 0; j < m1.cols(); j++) {
      ret(i, j) = m1(i, j) - m2(i, j);
    }
  }
  return ret;
}

template <typename T> Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2) {
  if (!(m1.cols() == m2.cols() && m1.rows() == m2.rows())) {
    throw "Error: cannot calculate matrix div with different matrix size";
  }

  T sum;
  Matrix<T> ret(m1.rows(), m2.cols());
  for (int i = 0; i < m1.rows(); i++) {
    for (int j = 0; j < m1.cols(); j++) {
      sum = 0;
      for (int v = 0; v < m1.rows(); v++) {
        sum += m1(i, v) * m2(v, j);
      }
      ret(i, j) = sum;
    }
  }
  return ret;
}

template <typename T> Matrix<T> operator*(const Matrix<T> &m1, const T &val) {
  Matrix<T> ret(m1.rows(), m1.cols());
  for (int i = 0; i < m1.rows(); i++) {
    for (int j = 0; j < m1.cols(); j++) {
      ret(i, j) = m1(i, j) * val;
    }
  }
  return ret;
}

template <typename T> T &Matrix<T>::operator()(int row, int col) {
  if (!(row <= _rows && col <= _cols && row >= 0 && col >= 0)) {
    throw "Error: atempt to access to invalid matrix cell ranger";
  }

  return _matrix[row * this->_cols + col];
}

template <typename T> T &Matrix<T>::operator()(int row, int col) const {
  if (!(row <= _rows && col <= _cols && row >= 0 && col >= 0)) {
    throw "Error: atempt to access to invalid matrix cell ranger";
  }
  return _matrix[row * this->_cols + col];
}

template <typename T> T &Matrix<T>::operator[](const int ind) {
  if (!(ind <= _cols * _rows && ind >= 0)) {
    throw "Error: atempt to access to invalid matrix cell ranger";
  }
  return _matrix[ind];
}

template <typename T> T &Matrix<T>::operator[](const int ind) const {
  if (!(ind <= _cols * _rows && ind >= 0)) {
    throw "Error: atempt to access to invalid matrix cell ranger";
  }
  return _matrix[ind];
}

template <typename T> bool operator==(const Matrix<T> &m1, const Matrix<T> &m2) {
  if (!(m1._cols == m2._cols && m1._rows == m2._rows)) {
    throw "Error: cannot compare matrix with matrix different sizes";
  }

  const float epsilon = 0.00001;
  for (int i = 0; i < m1._rows; ++i) {
    for (int j = 0; j < m2._cols; ++j) {
      if (std::is_same<T, float>::value || std::is_same<T, double>::value) {
        if (!(std::abs(m1(i, j) - m2(i, j)) <=
              (std::max(std::abs(m1(i, j)), std::abs(m2(i, j))) * epsilon))) { // thanks, knoth
          return false;
        }
      } else {
        if (m1(i, j) != m2(i, j)) {
          return false;
        }
      }
    }
  }

  return true;
}

template <typename T> bool operator!=(const Matrix<T> &m1, const Matrix<T> &m2) {
  return !(m1 == m2);
}

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
  if (!(this->_cols == other._cols && this->_rows == other._rows)) {
    throw "Error: cannot compare matrix with matrix different sizes";
  }
  this->apply([&other](int r, int c, T cur) -> T { return other(r, c); });
  return *this;
}

static int get_float_digits(double num) {
  int digits = 0;
  double ori = num;
  long num2 = num;
  while (num2 > 0) {
    digits++;
    num2 = num2 / 10;
  }
  if (ori == 0)
    digits = 1;
  num = ori;
  double no_float;
  no_float = ori * (pow(10, (16 - digits)));
  long long int total = (long long int)no_float;
  int no_of_digits, extrazeroes = 0;
  for (int i = 0; i < 16; i++) {
    int dig;
    dig = total % 10;
    total = total / 10;
    if (dig != 0)
      break;
    else
      extrazeroes++;
  }
  no_of_digits = 16 - extrazeroes;
  return no_of_digits;
}

template <typename T> std::ostream &operator<<(std::ostream &out, const Matrix<T> &mtx) {
  unsigned int max_len;
  {
    std::string buf;
    unsigned int cur_len = 0;
    max_len = 0;
    for (int l_row = 0; l_row < mtx._rows; l_row++) {
      for (int l_col = 0; l_col < mtx._cols; l_col++) {
        cur_len = get_float_digits(mtx(l_row, l_col));
        if (mtx(l_row, l_col) < 0) {
          cur_len++;
        }
        if (cur_len > max_len) {
          max_len = cur_len;
        }
      }
    }
  }

  std::string prefix("Matrix[" + std::to_string(mtx.rows()) + ", " + std::to_string(mtx.rows()) +
                     "] = ");
  out << prefix;

  const int token_syms = 2; // todo
  for (int l_row = 0; l_row < mtx.rows(); l_row++) {
    if (l_row > 0) { // white spaces
      for (int i = 0; i < prefix.length(); i++) {
        out << " ";
      }
    }
    out << "| ";
    for (int l_col = 0; l_col < mtx.cols(); l_col++) {
      /* out << std::setw(max_len) << std::setprecision(token_syms) <<
       * mtx(l_row, l_col); */
      out << std::setw(max_len) << mtx(l_row, l_col);
      if (l_col != mtx.cols() - 1) {
        out << ", ";
      }
    }
    out << " |" << std::endl;
  }

  return out;
}

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <stdexcept>
#include <ostream>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, std::size_t Rows, std::size_t Cols>
class Matrix {
 public:
  T data[Rows][Cols];

  constexpr std::size_t RowsNumber() const noexcept {
    return Rows;
  }

  constexpr std::size_t ColumnsNumber() const noexcept {
    return Cols;
  }

  T& operator()(std::size_t row, std::size_t col) {
    return data[row][col];
  }

  const T& operator()(std::size_t row, std::size_t col) const {
    return data[row][col];
  }

  T& At(std::size_t row, std::size_t col) {
    if (row >= Rows || col >= Cols) {
      throw MatrixOutOfRange{};
    }
    return data[row][col];
  }

  const T& At(std::size_t row, std::size_t col) const {
    if (row >= Rows || col >= Cols) {
      throw MatrixOutOfRange{};
    }
    return data[row][col];
  }
};

template <typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Cols, Rows> GetTransposed(const Matrix<T, Rows, Cols>& matrix) {
  Matrix<T, Cols, Rows> result{};
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      result(j, i) = matrix(i, j);
    }
  }
  return result;
}
template <typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols>& operator+=(
    Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      lhs(i, j) += rhs(i, j);
    }
  }
  return lhs;
}

template <typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols>& operator-=(
    Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      lhs(i, j) -= rhs(i, j);
    }
  }
  return lhs;
}
template <typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> operator+(
    const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
  Matrix<T, Rows, Cols> result = lhs;
  result += rhs;
  return result;
}

template <typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> operator-(
    const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
  Matrix<T, Rows, Cols> result = lhs;
  result -= rhs;
  return result;
}
template <typename T, std::size_t R, std::size_t K, std::size_t C>
Matrix<T, R, C> operator*(const Matrix<T, R, K>& lhs, const Matrix<T, K, C>& rhs) {
  Matrix<T, R, C> result{};
  for (std::size_t i = 0; i < R; ++i) {
    for (std::size_t j = 0; j < C; ++j) {
      for (std::size_t k = 0; k < K; ++k) {
        result(i, j) += lhs(i, k) * rhs(k, j);
      }
    }
  }
  return result;
}
template <typename T, std::size_t R, std::size_t K, std::size_t C>
Matrix<T, R, C>& operator*=(Matrix<T, R, C>& lhs, const Matrix<T, C, K>& rhs) {
  lhs = lhs * rhs;
  return lhs;
}
template <typename T, std::size_t Rows, std::size_t Cols, typename U>
Matrix<T, Rows, Cols>& operator*=(Matrix<T, Rows, Cols>& matrix, const U& scalar) {
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      matrix(i, j) *= scalar;
    }
  }
  return matrix;
}

template <typename T, std::size_t Rows, std::size_t Cols, typename U>
Matrix<T, Rows, Cols>& operator/=(Matrix<T, Rows, Cols>& matrix, const U& scalar) {
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      matrix(i, j) /= scalar;
    }
  }
  return matrix;
}
template <typename T, std::size_t Rows, std::size_t Cols, typename U>
Matrix<T, Rows, Cols> operator*(Matrix<T, Rows, Cols> matrix, const U& scalar) {
  matrix *= scalar;
  return matrix;
}

template <typename T, std::size_t Rows, std::size_t Cols, typename U>
Matrix<T, Rows, Cols> operator*(const U& scalar, Matrix<T, Rows, Cols> matrix) {
  matrix *= scalar;
  return matrix;
}

template <typename T, std::size_t Rows, std::size_t Cols, typename U>
Matrix<T, Rows, Cols> operator/(Matrix<T, Rows, Cols> matrix, const U& scalar) {
  matrix /= scalar;
  return matrix;
}
template <typename T, std::size_t Rows, std::size_t Cols>
bool operator==(const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      if (lhs(i, j) != rhs(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <typename T, std::size_t Rows, std::size_t Cols>
bool operator!=(const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
  return !(lhs == rhs);
}


template <typename T, std::size_t Rows, std::size_t Cols>
std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Cols>& matrix) {
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      if (j > 0) {
        os << ' ';
      }
      os << matrix(i, j);
    }
    os << '\n';
  }
  return os;
}

template <typename T, std::size_t Rows, std::size_t Cols>
std::istream& operator>>(std::istream& is, Matrix<T, Rows, Cols>& matrix) {
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      is >> matrix(i, j);
    }
  }
  return is;
}
#endif  // MATRIX_H_
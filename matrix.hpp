#ifndef WRAPPER_MATRIX_H_
#define WRAPPER_MATRIX_H_

#include <initializer_list>
#include <vector>
// #include <iterator>
#include <stdexcept>
// #include <utility>

// TODO(#5): Transpose method
// TODO(#6): Identity matrix method
// TODO(#7): Invertible matrix function

template <size_t Rows, size_t Columns, typename T>
class Matrix final {
 private:
  const size_t cap_ = Rows * Columns;
  std::vector<T> container_;
  size_t sz_ = 0;

  template <bool>
  T determinant_impl() = delete;

  template <>
  T determinant_impl<true>() {
    // TODO(#3): Determinant function
  }

 public:
  Matrix() = default;

  explicit Matrix(const T &value) : container_(cap_, value), sz_(cap_) {}

  Matrix(std::initializer_list<T> ilist)
      : container_(ilist),
        sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  Matrix(T *begin, T *end)
      : container_(begin, end),
        sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  template <typename InputIt>
  Matrix(InputIt begin, InputIt end)
      : container_(begin, end),
        sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  Matrix(const std::vector<T> &other_container)
      : container_(other_container),
        sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  size_t size() const { return sz_; }

  size_t capacity() const { return cap_; }

  size_t rows() const { return Rows; }

  size_t columns() const { return Columns; }

  T determinant() const { return determinant_imp<Rows == Columns>(); }

  T &operator()(size_t row, size_t column) {
    return container_[column + (row * Columns)];
  }

  const T &operator()(size_t row, size_t column) const {
    return container_[column + (row * Columns)];
  }

  T &at(size_t row, size_t column) {
    if (row >= Rows || column >= Columns) {
      throw std::out_of_range("Invalid index");
    }
    return container_[column + (row * Columns)];
  }

  const T &at(size_t row, size_t column) const {
    if (row >= Rows || column >= Columns) {
      throw std::out_of_range("Invalid index");
    }
    return container_[column + (row * Columns)];
  }

  Matrix<Rows, Columns, T> &operator+=(const Matrix<Rows, Columns, T> &matrix) {
    for (size_t ind = 0; ind < sz_; ++ind) {
      container_[ind] += matrix.container_[ind];
    }
    return *this;
  }

  Matrix<Rows, Columns, T> &operator-=(const Matrix<Rows, Columns, T> &matrix) {
    for (size_t ind = 0; ind < sz_; ++ind) {
      container_[ind] -= matrix.container_[ind];
    }
    return *this;
  }

  template <typename U>
  Matrix<Rows, Columns, T> &operator*=(const U &value) {
    for (auto &val : container_) {
      val *= value;
    }
    return *this;
  }
};

template <size_t Rows, size_t Columns, typename T>
bool operator==(Matrix<Rows, Columns, T> &left,
                Matrix<Rows, Columns, T> &right) {
  if (left.size() != right.size()) {
    return false;
  }

  for (size_t row = 0; row < Rows; ++row) {
    for (size_t column = 0; column < Columns; ++column) {
      if (left(row, column) != right(row, column)) {
        return false;
      }
    }
  }

  return true;
}

template <size_t Rows, size_t Columns, typename T, typename U>
Matrix<Rows, Columns, T> operator*(const Matrix<Rows, Columns, T> &matrix,
                                   const U &value) {
  Matrix<Rows, Columns, T> copy = matrix;
  copy *= value;
  return copy;
}

template <size_t Rows, size_t Columns, typename T, typename U>
Matrix<Rows, Columns, T> operator*(const U &value,
                                   const Matrix<Rows, Columns, T> &matrix) {
  Matrix<Rows, Columns, T> copy = matrix;
  copy *= value;
  return copy;
}

template <size_t Rows, size_t K, size_t Columns, typename T>
Matrix<Rows, Columns, T> operator*(const Matrix<Rows, K, T> &left,
                                   const Matrix<K, Columns, T> &right) {
  std::vector<T> pre_result;
  pre_result.reserve(Rows * Columns);
  for (size_t row = 0; row < Rows; ++row) {
    for (size_t column = 0; column < Columns; ++column) {
      T sum = 0;
      for (size_t k = 0; k < K; ++k) {
        sum += left(row, k) * right(k, column);
      }
      pre_result.push_back(sum);
    }
  }
  Matrix<Rows, Columns, T> result(pre_result);
  return result;
}

template <size_t Rows, size_t Columns, typename T>
Matrix<Rows, Columns, T> operator+(const Matrix<Rows, Columns, T> &left,
                                   const Matrix<Rows, Columns, T> &right) {
  Matrix<Rows, Columns, T> copy = left;
  copy += right;
  return copy;
}

template <size_t Rows, size_t Columns, typename T>
Matrix<Rows, Columns, T> operator-(const Matrix<Rows, Columns, T> &left,
                                   const Matrix<Rows, Columns, T> &right) {
  Matrix<Rows, Columns, T> copy = left;
  copy -= right;
  return copy;
}

template <size_t Rows, size_t Columns, typename T>
Matrix<Rows, Columns, T> operator+(Matrix<Rows, Columns, T> matrix) {
  return matrix;
}

template <size_t Rows, size_t Columns, typename T>
Matrix<Rows, Columns, T> operator-(Matrix<Rows, Columns, T> &matrix) {
  auto copy = matrix;
  copy *= -1;
  return copy;
}

#endif

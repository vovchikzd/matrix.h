#ifndef MATRIX_H_
#define MATRIX_H_

#include <initializer_list>
#include <vector>
#include <iterator>
#include <stdexcept>
// #include <utility>

// TODO(#3): Determinant function
// TODO(#5): Transpose method
// TODO(#6): Identity matrix method
// TODO(#7): Invertible matrix function

template <typename T, size_t Rows, size_t Columns,
          typename Container = std::vector<T>>
class Matrix final {
 private:
  const size_t cap_ = Rows * Columns;
  size_t sz_ = 0;
  Container container_;

 public:
  Matrix() = default;

  Matrix(const T& value): sz_(cap_), container_(cap_, value) {}

  Matrix(std::initializer_list<T> ilist): container_(ilist) {
    auto size = container_.size();
    sz_ = size >= cap_ ? cap_ : size;
  }

  Matrix(T *begin, T *end): container_(begin, end) {
    auto size = container_.size();
    sz_ = size >= cap_ ? cap_ : size;
  }

  template <typename InputIt>
  Matrix(InputIt begin, InputIt end): container_(begin, end) {
    auto size = container_.size();
    sz_ = size >= cap_ ? cap_ : size;
  }

  Matrix(const Container &other_container): container_(other_container) {
    auto size = container_.size();
    sz_ = size >= cap_ ? cap_ : size;
  }

  size_t size() const { return sz_; }

  size_t capacity() const { return cap_; }

  size_t rows() const { return Rows; }

  size_t columns() const { return Columns; }

  Matrix<T, Rows, Columns, Container> &operator+=(
      const Matrix<T, Rows, Columns, Container> &matrix) {
    for (size_t ind = 0; ind < sz_; ++ind) {
      container_[ind] += matrix.container_[ind];
    }
    return *this;
  }

  Matrix<T, Rows, Columns, Container> &operator-=(
      const Matrix<T, Rows, Columns, Container> &matrix) {
    for (size_t ind = 0; ind < sz_; ++ind) {
      container_[ind] -= matrix.container_[ind];
    }
    return *this;
  }

  Matrix<T, Rows, Columns, Container> &operator*=(const T &value) {
    for (auto& val: container_) {
      val *= value;
    }
    return *this;
  }

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
    return values[column + (row * Columns)];
  }

  const T &at(size_t row, size_t column) const {
    if (row >= Rows || column >= Columns) {
      throw std::out_of_range("Invalid index");
    }
    return values[column + (row * Columns)];
  }

};

template <typename T, size_t Rows, size_t Columns,
          template <typename> class Alloc>
bool operator==(Matrix<T, Rows, Columns, Alloc> &left,
                Matrix<T, Rows, Columns, Alloc> &right) {
  for (size_t i = 0; i < left.size(); ++i) {
    if (left[i] != right[i]) return false;
  }
  return true;
}

template <typename T, size_t Rows, size_t Columns,
          template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator*(
    const Matrix<T, Rows, Columns, Allocator> &matrix, const T &value) {
  auto copy = matrix;
  copy *= value;
  return copy;
}

template <typename T, size_t Rows, size_t Columns,
          template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator*(
    const T &value, const Matrix<T, Rows, Columns, Allocator> &matrix) {
  auto copy = matrix;
  copy *= value;
  return copy;
}

template <typename T, size_t Rows, size_t K, size_t Columns,
          template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator*(
    const Matrix<T, Rows, K, Allocator> &left,
    const Matrix<T, K, Columns, Allocator> &right) {
  Matrix<T, Rows, Columns, Allocator> result;
  for (size_t row = 0; row < Rows; ++row) {
    for (size_t column = 0; column < Columns; ++column) {
      T sum = 0;
      for (size_t k = 0; k < K; ++k) {
        sum += left(row, k) * right(k, column);
      }
      result.push_back(sum);
    }
  }
  return result;
}

template <typename T, size_t Rows, size_t Columns,
          template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator+(
    const Matrix<T, Rows, Columns, Allocator> &left,
    const Matrix<T, Rows, Columns, Allocator> &right) {
  auto copy = left;
  copy += right;
  return copy;
}

template <typename T, size_t Rows, size_t Columns,
          template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator-(
    const Matrix<T, Rows, Columns, Allocator> &left,
    const Matrix<T, Rows, Columns, Allocator> &right) {
  auto copy = left;
  copy -= right;
  return copy;
}

template <typename T, size_t Rows, size_t Columns,
          template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator+(
    Matrix<T, Rows, Columns, Allocator> &matrix) {
  return matrix;
}

template <typename T, size_t Rows, size_t Columns,
          template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator-(
    Matrix<T, Rows, Columns, Allocator> &matrix) {
  auto copy = matrix;
  copy *= -1;
  return copy;
}

/*
template <typename T, size_t Size, template <typename> class Allocator>
T determinant(Matrix<T, Size, Size, Allocator>& matrix) {
    // implement
}
*/

emun class MatrixType {};

#endif

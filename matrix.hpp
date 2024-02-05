#ifndef WRAPPER_MATRIX_H_
#define WRAPPER_MATRIX_H_

#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <vector>

template <size_t Rows, size_t Columns, typename T>
class Matrix final {
 private:
  size_t cap_ = Rows * Columns;
  std::vector<T> container_;
  size_t sz_ = 0;

  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

 public:
  Matrix() = default;

  Matrix(const T &value) : container_(cap_, value), sz_(cap_) {}

  Matrix(std::initializer_list<T> ilist)
      : container_(ilist)
      , sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  Matrix(T *begin, T *end)
      : container_(begin, end)
      , sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  template <typename InputIt>
  Matrix(InputIt begin, InputIt end)
      : container_(begin, end)
      , sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  Matrix(const std::vector<T> &container)
      : container_(container)
      , sz_(container_.size() >= cap_ ? cap_ : container_.size()) {}

  size_t size() const { return sz_; }

  size_t capacity() const { return cap_; }

  size_t rows() const { return Rows; }

  size_t columns() const { return Columns; }

  bool empty() const { return sz_ == 0; }

  iterator begin() { return container_.begin(); }

  const_iterator begin() const { return container_.cbegin(); }

  const_iterator cbegin() const { return container_.cbegin(); }

  iterator end() {
    return container_.size() <= cap_ ? container_.end()
                                     : container_.begin() + cap_;
  }

  const_iterator end() const {
    return container_.size() <= cap_ ? container_.cend()
                                     : container_.cbegin() + cap_;
  }

  const_iterator cend() const {
    return container_.size() <= cap_ ? container_.cend()
                                     : container_.cbegin() + cap_;
  }

  T &operator()(size_t row, size_t column) {
    return container_[column + (row * Columns)];
  }

  const T &operator()(size_t row, size_t column) const {
    return container_[column + (row * Columns)];
  }

  T &at(size_t row, size_t column) {
    size_t index = column + (row * Columns);
    if (index >= sz_ || row >= Rows || column >= Columns) {
      throw std::out_of_range("Invalid index");
    }
    return container_[index];
  }

  const T &at(size_t row, size_t column) const {
    size_t index = column + (row * Columns);
    if (index >= sz_ || row >= Rows || column >= Columns) {
      throw std::out_of_range("Invalid index");
    }
    return container_[index];
  }

  void assign(const T& value) {
    container_.assign(cap_, value);
  }

  void assign(std::initializer_list<T> ilist) {
    container_.assign(ilist);
  }

  void assign(std::vector<T>& other) {
    contaier_.assign(other.begin(), other.end());
  }

  template <typename InputIt>
  void assign(InputIt begin, InputIt end) {
    container_.assign(begin, end);
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
    for (auto &&val : container_) { val *= value; }
    return *this;
  }
};

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
Matrix<Rows, Columns, T> operator+(Matrix<Rows, Columns, T>& matrix) {
  auto copy = matrix;
  return copy;
}

template <size_t Rows, size_t Columns, typename T>
Matrix<Rows, Columns, T> operator-(Matrix<Rows, Columns, T> &matrix) {
  auto copy = matrix;
  copy *= -1;
  return copy;
}

#endif

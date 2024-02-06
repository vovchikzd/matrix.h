#ifndef WRAPPER_MATRIX_MATH_H_
#define WRAPPER_MATRIX_MATH_H_

#include <algorithm>

#include "matrix.hpp"

template <size_t Rows, size_t Columns, typename T>
void swap_rows(Matrix<Rows, Columns, T>& matrix, size_t first_row,
               size_t second_row) {
  for (size_t column = 0; column < Columns; ++column) {
    std::swap(matrix(first_row, column), matrix(second_row, column));
  }
}

template <size_t Rows, size_t Columns, typename T>
void swap_columns(Matrix<Rows, Columns, T>& matrix, size_t first_col,
                  size_t second_col) {
  for (size_t row = 0; row < Rows; ++row) {
    std::swap(matrix(row, first_col), matrix(row, second_col));
  }
}

template <size_t Rows, size_t Columns, typename T>
Matrix<Columns, Rows, T> transpose(const Matrix<Rows, Columns, T>& matrix) {
  std::vector<T> pre_result;
  pre_result.reserve(Rows * Columns);
  for (size_t column = 0; column < Columns; ++column) {
    for (size_t row = 0; row < Rows; ++row) {
      pre_result.push_back(matrix(row, column));
    }
  }
  Matrix<Columns, Rows, T> result(pre_result);
  return result;
}

template <size_t K, typename T>
T determinant(Matrix<K, K, T> matrix) {}

template <size_t K, typename T>
Matrix<K, K, T> invertible(Matrix<K, K, T> matrix) {}

template <size_t Rows, size_t Columns, typename T>
void mult_row(Matrix<Rows, Columns, T>& matrix, size_t row, T& value)  {
  for (size_t column = 0; column < Columns; ++column) {
    matrix(row, column) *= value;
  }
}

template <size_t Rows, size_t Columns, typename T>
void mult_column(Matrix<Rows, Columns, T>& matrix, size_t column, T& value)  {
  for (size_t row = 0; row < Rows; ++row) {
    matrix(row, column) *= value;
  }
}

template <size_t Rows, size_t Columns, typename T>
void add_rows(Matrix<Rows, Columns, T>& matrix, size_t src, size_t target) {
  for (size_t column = 0; column < Columns; ++column) {
    matrix(target, column) += matrix(src, column);
  }
}

template <size_t Rows, size_t Columns, typename T>
void add_columns(Matrix<Rows, Columns, T>& matrix, size_t src, size_t target) {
  for (size_t row = 0; row < Rows; ++row) {
    matrix(row, target) += matrix(row, src);
  }
} 

#endif

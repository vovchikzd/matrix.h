#ifndef MATRIX_H
#define MATRIX_H

#include <utility> // std::pair

template <size_t M, size_t N, typename T>
class Matrix {

};

template <size_t M, size_t N, size_t K, typename T>
Matrix<M, K, T> operator*(const Matrix<M, N, T>&, const Matrix<N, K, T>&) {
    
}

template <size_t M, size_t N, typename T>
Matrix<M, N, T> operator+(const Matrix<M, N, T>&, const Matrix<M, N, T>&) {

}

#endif

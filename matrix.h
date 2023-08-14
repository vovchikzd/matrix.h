#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <array>

template <typename T, size_t M, size_t N>
class Matrix {
    const size_t capacity = M + N;
    size_t size = 0;

public:
    Matrix() = default;

    void push_back(const T&);

    void push_back(const T*, const T*);
    Matrix(const T*, const T*);

    void push_back(const std::array<T, N>&);
    Matrix(const std::array<T, N>&);

    template <template <typename> class Container>
    void push_back(const Container<T>&);
    
    template <template <typename> class Container>
    Matrix(const Container<T>&);

    ~Matrix() = default; // don't forget

};

template <typename T, size_t M, size_t N>
void Matrix<T, M, N>::push_back(const T& value) {

}

template <typename T, size_t M, size_t N>
void Matrix<T, M, N>::push_back(const T* begin, const T* end) {
    for(; begin < end; ++begin) {
        this->push_back(*begin);
    }
}

template <typename T, size_t M, size_t N>
void Matrix<T, M, N>::push_back(const std::array<T, N>& array) {
    for(auto it = array.begin(), end = array.end(); it != end; ++it) {
        this->push_bak(*it);
    }
}

template <typename T, size_t M, size_t N>
template <template <typename> class Container>
void Matrix<T, M, N>::push_back(const Container<T>& container) {
    for(auto it = container.begin(), end = container.end(); it != end; ++it) {
        this->push_back(*it);
    }
}

template <typename T, size_t M, size_t N, size_t K>
Matrix<T, M, K> operator*(const Matrix<T, M, N>&, const Matrix<T, N, K>&) {
    
}

template <typename T, size_t M, size_t N>
Matrix<T, M, N> operator+(const Matrix<T, M, N>&, const Matrix<T, M, N>&) {

}

#endif
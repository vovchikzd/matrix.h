#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <array>

template <typename T, size_t Rows, size_t Columns,
         template <typename> class Allocator = std::allocator>
class Matrix {
    public:
    const size_t capacity = Rows + Columns;
    size_t size = 0;
    //Allocator = 

public:
    Matrix() = default;

    void push_back(const T&);

    void push_back(const T*, const T*);
    Matrix(const T*, const T*);

    /* What size? Random? So, another template
    void push_back(const std::array<T, Columns>&);
    Matrix(const std::array<T, N>&);
    */

    template <template <typename> class Container>
    void push_back(const Container<T>&);
    
    template <template <typename> class Container>
    Matrix(const Container<T>&);


    ~Matrix() = default; // don't forget

    T determinant();

};

template <typename T, size_t Rows, size_t Columns,
         template <typename> class Allocator>
void Matrix<T, Rows, Columns, Allocator>::push_back(const T& value) {

}

template <typename T, size_t Rows, size_t Columns,
         template <typename> class Allocator>
void Matrix<T, Rows, Columns, Allocator>::push_back(const T* begin, const T* end) {
    for(; begin < end; ++begin) {
        this->push_back(*begin);
    }
}

/*
template <typename T, size_t Rows, size_t N>
void Matrix<T, Rows, N>::push_back(const std::array<T, N>& array) {
    for(auto it = array.begin(), end = array.end(); it != end; ++it) {
        this->push_bak(*it);
    }
}
*/

template <typename T, size_t Rows, size_t Columns,
         template <typename> class Allocator>
template <template <typename> class Container>
void Matrix<T, Rows, Columns, Allocator>::push_back(const Container<T>& container) {
    for(auto it = container.begin(), end = container.end(); it != end; ++it) {
        this->push_back(*it);
    }
}

template <typename T, size_t Rows, size_t K, size_t Columns>
Matrix<T, Rows, Columns> operator*(const Matrix<T, Rows, K>&, const Matrix<T, K, Columns>&) {
    
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns>&, const Matrix<T, Rows, Columns>&) {

}

template <typename T, size_t Rows>
T determinant(Matrix<T, Rows, Rows>& matrix) {

}

#endif

#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <exception>
#include <array>

template <typename T, size_t Rows, size_t Columns,
         template <typename> class Allocator = std::allocator>
class Matrix {
private:

    const size_t capacity = Rows + Columns;
    size_t size = 0;
    Allocator<T*> ptr_alloc;
    Allocator<T> type_alloc;
    T** rows_ptrs = nullptr;

    using ptr_alloc_traits = std::allocator_traits<Allocator<T*>>;
    using type_alloc_traits = std::allocator_traits<Allocator<T>>;

public:

    Matrix() {
        rows_ptrs = ptr_alloc_traits::allocate(ptr_alloc, Rows); 
        for(size_t i = 0; i < Rows; ++i) {
            T* row = type_alloc_traits::allocate(type_alloc, Columns);
            ptr_alloc_traits::construct(ptr_alloc, rows_ptrs + i, row);
        }
    }

    void push_back(const T&);

    Matrix(const T*, const T*): Matrix() {
        
    }

    template <size_t Number>
    Matrix(const std::array<T, Number>&): Matrix() {
        
    }
    
    template <template <typename> class Container>
    Matrix(const Container<T>&): Matrix() {

    }

    template <typename Iter>
    Matrix(Iter bergin, Iter end): Matrix() {

    }

    ~Matrix() {
        
    }
};

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

#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <exception>
#include <initializer_list>

// TODO(#1): Iterators
// TODO(#2): Multiplication
// TODO(#3): Determinant function
// TODO(#4): Move semantic
// TODO: Transpose method
// TODO: Identity matrix method
// TODO: Invertible matrix function
// TODO: Rewrite assignment operator

template <typename T, size_t Rows, size_t Columns,
         template <typename> class Allocator = std::allocator>
class Matrix {
private:

    const size_t cap = Rows * Columns;
    size_t sz = 0;
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

    Matrix(std::initializer_list<T> list) {
        for(auto it = list.begin(), end = list.end(); it != end; ++it) {
            push_back(*it);
        }
    }

    Matrix(const T* begin, const T* end): Matrix() {
        for (;begin != end; ++begin) {
            push_back(*begin);
        }
    }

    template <typename Iter>
    Matrix(Iter begin, Iter end): Matrix() {
        for (;begin != end; ++begin) {
            push_back(*begin);
        }
    }

    Matrix(const Matrix<T, Rows, Columns, Allocator>& matrix): Matrix() {
        for (size_t i = 0; i < matrix.size(); ++i) {
            push_back(matrix[i]);
        }
    }

    void push_back(const T& value) {
        size_t first_index = sz / Columns;
        size_t second_index = sz - (first_index * Columns);
        type_alloc_traits::construct(type_alloc,
                rows_ptrs[first_index] + second_index, value);
        ++sz;
    }

    void push_back(const T* begin, const T* end) {
        for (; begin != end; ++begin) {
            push_back(*begin);
        }
    }

    template <typename Iter>
    void push_back(Iter begin, Iter end) {
        for (; begin != end; ++begin) {
            push_back(*begin);
        }
    }
    
    size_t size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    size_t capacity() const {
        return cap;
    }

    Matrix<T, Rows, Columns, Allocator>& operator=(const Matrix<T, Rows, Columns, Allocator>& matrix) {
        for (; sz > matrix.size(); --sz) {
            size_t first_index = sz / Columns;
            size_t second_index = sz - (first_index * Columns);
            type_alloc_traits::destroy(type_alloc,
                    rows_ptrs[first_index] + second_index);
        }

        for (size_t i = 0; i < sz; ++i) {
            (*this)[i] = matrix[i];
        }

        return *this;
        
    }

    Matrix<T, Rows, Columns, Allocator>& operator+=(const Matrix<T, Rows, Columns, Allocator>& matrix) {
        for (size_t i = 0; i < sz; ++i) {
            (*this)[i] += matrix[i];
        }
        return *this;
    }

    Matrix<T, Rows, Columns, Allocator>& operator-=(const Matrix<T, Rows, Columns, Allocator>& matrix) {
        for (size_t i = 0; i < sz; ++i) {
            (*this)[i] -= matrix[i];
        }
        return *this;
    }

    Matrix<T, Rows, Columns, Allocator>& operator*=(const T& value) {
        for (size_t i = 0; i < sz; ++i) {
            (*this)[i] *= value;
        }
        return *this;
    }

    Matrix<T, Rows, Columns, Allocator>& operator*=(const Matrix<T, Rows, Columns, Allocator>& matrix) {
        // implement
        return *this;
    }

    T& operator[](size_t number) {
        size_t first_index = number / Columns;
        size_t second_index = number - (first_index * Columns);
        return rows_ptrs[first_index][second_index];
    }

    const T& operator[](size_t number) const {
        size_t first_index = number / Columns;
        size_t second_index = number - (first_index * Columns);
        return rows_ptrs[first_index][second_index];
    }

    T& operator()(size_t first, size_t second) {
        return rows_ptrs[first][second];
    }

    const T& operator()(size_t first, size_t second) const {
        return rows_ptrs[first][second];
    }

    T& at(size_t number) {
        if (number > sz) throw std::out_of_range("Invalid index");        
        size_t first_index = number / Columns;
        size_t second_index = number - (first_index * Columns);
        return rows_ptrs[first_index][second_index];
    }

    const T& at(size_t number) const {
        if (number > sz) throw std::out_of_range("Invalid index");        
        size_t first_index = number / Columns;
        size_t second_index = number - (first_index * Columns);
        return rows_ptrs[first_index][second_index];
    }

    T& at(size_t first, size_t second) {
        if (first >= Rows || second >= Columns) throw std::out_of_range("Invalid index");        
        return rows_ptrs[first][second];
    }

    const T& at(size_t first, size_t second) const {
        if (first >= Rows || second >= Columns) throw std::out_of_range("Invalid index");        
        return rows_ptrs[first][second];
    }

    ~Matrix() {
        for (; sz > 0; --sz) {
            size_t first_index = sz / Columns;
            size_t second_index = sz - (first_index * Columns);
            type_alloc_traits::destroy(type_alloc,
                    rows_ptrs[first_index] + second_index);
        }

        for (size_t i = 0; i < Rows; ++i) {
            type_alloc_traits::deallocate(type_alloc, rows_ptrs[i], Columns);
        }

        ptr_alloc_traits::deallocate(ptr_alloc, rows_ptrs, Rows);
    }
};

template <typename T, size_t Rows, size_t Columns, template <typename> class Alloc>
bool operator==(Matrix<T, Rows, Columns, Alloc>& left, Matrix<T, Rows, Columns, Alloc>& right) {
    for (size_t i = 0; i < left.size(); ++i) {
        if (left[i] != right[i]) return false;
    }
    return true;
}

template <typename T, size_t Rows, size_t Columns, template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator*(const Matrix<T, Rows, Columns, Allocator>& matrix,
        const T& value) {
    auto copy = matrix;
    copy *= value;
    return copy;
}

template <typename T, size_t Rows, size_t Columns, template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator*(const T& value,
        const Matrix<T, Rows, Columns, Allocator>& matrix) {
    auto copy = matrix;
    copy *= value;
    return copy;
}

template <typename T, size_t Rows, size_t K, size_t Columns, template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator*(const Matrix<T, Rows, K, Allocator>& left,
        const Matrix<T, K, Columns, Allocator>& right) {
    auto copy = left;
    copy *= right;
    return copy;
}

template <typename T, size_t Rows, size_t Columns, template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator+(const Matrix<T, Rows, Columns, Allocator>& left,
        const Matrix<T, Rows, Columns, Allocator>& right) {
    auto copy = left;
    copy += right;
    return copy;
}

template <typename T, size_t Rows, size_t Columns, template <typename> class Allocator>
Matrix<T, Rows, Columns, Allocator> operator-(const Matrix<T, Rows, Columns, Allocator>& left,
        const Matrix<T, Rows, Columns, Allocator>& right) {
    auto copy = left;
    copy -= right;
    return copy;
}

template <typename T, size_t Size, template <typename> class Allocator>
T determinant(Matrix<T, Size, Size, Allocator>& matrix) {
    // implement
}

#endif

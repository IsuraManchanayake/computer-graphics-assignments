#ifndef MATRIX_H
#define MATRIX_H

#include "cg-utils_global.h"
#include "vector.h"

#include <cstddef>
#include <ostream>
#include <cmath>
#include <cassert>
#include <algorithm>

CGUTILS_NAMESPACE_BEGIN

template<size_t N>
struct Matrix;

template<size_t N>
struct CGUTILSSHARED_EXPORT MatrixSlice {
    Matrix<N>& mat;
    size_t i = 0;

    MatrixSlice(Matrix<N>& mat, const size_t i);
    double& operator[](size_t j);
    double operator[](size_t j) const;
    operator Vector<N>() const;
    MatrixSlice<N>& operator=(const Vector<N>& rhs);

    template<size_t M> friend Vector<M> CGUTILSSHARED_EXPORT operator*(const MatrixSlice<M>& lhs, const Matrix<M>& rhs);
    template<size_t M> friend std::ostream& CGUTILSSHARED_EXPORT operator<<(std::ostream& os, const MatrixSlice<M>& ms);
};

template <size_t N>
struct CGUTILSSHARED_EXPORT Matrix {
    double m[N][N];
    enum { dim = N };

    Matrix();
    Matrix(double m[N][N]);
    template<typename T> Matrix(std::initializer_list<std::initializer_list<T>> m);
    template<size_t M> Matrix(std::initializer_list<Vector<M>> vs);
    static Matrix<N> eye(void);
    static Matrix<N> zero(void);
    static Matrix<N> traslation_mat(const Vector<N>& trn);
//    static Matrix<N> rotation_mat(const Vector<N>& rot);
    static Matrix<N> scale_mat(const Vector<N>& fac);
    static Matrix<N> scale_mat(double fac);

    Matrix<N> operator+(const Matrix<N>& rhs) const;
    Matrix<N> operator-() const;
    Matrix<N> operator+() const;
    Matrix<N> operator-(const Matrix<N>& rhs) const;
    Matrix<N> operator*(const double rhs) const;
    Matrix<N>& operator*=(const double rhs);
    Matrix<N> operator*(const Matrix<N>& rhs) const;
    Matrix<N>& operator*=(const Matrix<N>& rhs);
    Matrix<N> operator/(const double rhs) const;
    MatrixSlice<N> operator[](const size_t rhs);
    bool operator==(const Matrix<N>& rhs) const;
    bool operator!=(const Matrix<N>& rhs) const;
    Matrix<N> transpose(void) const;

    template<size_t M> friend Matrix<M> CGUTILSSHARED_EXPORT operator*(const double lhs, const Matrix<M>& rhs);
    template<size_t M> friend Vector<M> CGUTILSSHARED_EXPORT operator*(const Vector<M>& lhs, const Matrix<M>& rhs);
    template<size_t M> friend Vector<M>& CGUTILSSHARED_EXPORT operator*=(Vector<M>& lhs, const Matrix<M>& rhs);
    template<size_t M> friend std::ostream& CGUTILSSHARED_EXPORT operator<<(std::ostream& os, const Matrix& rhs);
};

#include "matrix.tpp"

CGUTILS_NAMESPACE_END

#endif // MATRIX_H

#ifndef MATRIX_H
#define MATRIX_H

#include "cg-utils_global.h"

#include <cstddef>
#include <ostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <type_traits>

template<size_t N>
struct CGUTILSSHARED_EXPORT Vector {
    double v[N];

    Vector();
    Vector(double v[N]);
    template<typename T> Vector(const std::initializer_list<T>& v);
    static Vector<N> one(void);
    static Vector<N> zero(void);
    template<typename... T> static Vector<N> vec(T... vs);

    Vector<N> operator+(const Vector<N>& rhs) const;
    Vector<N> operator-() const;
    Vector<N> operator+() const;
    Vector<N> operator-(const Vector<N>& rhs) const;
    Vector<N> operator*(const double rhs) const;
    Vector<N> operator/(const double rhs) const;
    double dot(const Vector<N>& rhs) const;
    double norm(void) const;
    double dist(const Vector<N>& rhs) const;
    double cos(const Vector<N>& rhs) const;
    double angle(const Vector<N>& rhs) const;
    Vector<N> unit(void) const;
    double& operator[](const size_t rhs);
    const double& operator[](const size_t rhs) const;
    bool operator==(const Vector<N>& rhs) const;
    bool operator!=(const Vector<N>& rhs) const;
    double& x(void);
    double x(void) const;
    double& y(void);
    double y(void) const;
    double& z(void);
    double z(void) const;
    double& w(void);
    double w(void) const;
    template<size_t M> operator Vector<M>() const;

    friend Vector operator*(const double lhs, const Vector& rhs) {
        return rhs * lhs;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& rhs) {
        for(size_t i = 0; i < N; i++) {
            os << rhs.v[i] << ' ';
        }
        return os;
    }
};

template<size_t N>
Vector<N>::Vector() {
    for(size_t i = 0; i < N; i++) {
        v[i] = 0;
    }
}

template<size_t N>
Vector<N>::Vector(double v[N]) : v(v) {
}

template<size_t N>
template<typename T>
Vector<N>::Vector(const std::initializer_list<T>& v) : v() {
    static_assert(std::is_convertible<T, double>::value, "Type T should be convertible to double");
    std::transform(std::begin(v), std::end(v),
              std::begin(this->v), [](const T& e) {return static_cast<double>(e);});
}

template<size_t N>
template<typename... T>
Vector<N> Vector<N>::vec(T... vs) {
    Vector vv;
    auto vt = {vs...};
    assert(vt.size() > 0 && vt.size() <= N);
    std::copy(std::begin(vt), std::end(vt), std::begin(vv.v));
    return vv;
}

template<size_t N>
Vector<N> Vector<N>::one(void) {
    Vector<N> vec;
    for(size_t i = 0; i < N; i++) {
        vec.v[i] = 1;
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::zero(void) {
    return Vector<N>();
}

template<size_t N>
Vector<N> Vector<N>::operator+(const Vector<N>& rhs) const {
    Vector<N> vec(*this);
    for(size_t i = 0; i < N; i++) {
        vec.v[i] += rhs.v[i];
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::operator-() const {
    Vector<N> vec(*this);
    for(size_t i = 0; i < N; i++) {
        vec.v[i] *= -1;
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::operator+() const {
    return *this;
}

template<size_t N>
Vector<N> Vector<N>::operator-(const Vector<N>& rhs) const {
    return *this + (-rhs);
}

template<size_t N>
Vector<N> Vector<N>::operator*(const double rhs) const {
    Vector<N> vec(*this);
    for(size_t i = 0; i < N; i++) {
        vec.v[i] *= rhs;
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::operator/(const double rhs) const {
    return *this * (1 / rhs);
}

template<size_t N>
double& Vector<N>::x(void) {
    static_assert(N > 0, "Vector should be at least 1-D to retrieve x");
    return v[0];
}

template<size_t N>
double Vector<N>::x(void) const {
    return N > 0 ? v[0] : 0;
}

template<size_t N>
double& Vector<N>::y(void) {
    static_assert(N > 1, "Vector should be at least 2-D to retrieve y");
    return v[1];
}

template<size_t N>
double Vector<N>::y(void) const {
    return N > 1 ? v[1] : 0;
}

template<size_t N>
double& Vector<N>::z(void) {
    static_assert(N > 2, "Vector should be at least 3-D to retrieve z");
    return v[2];
}

template<size_t N>
double Vector<N>::z(void) const {
    return N > 2 ? v[2] : 0;
}

template<size_t N>
double& Vector<N>::w(void) {
    static_assert(N > 3, "Vector should be at least 4-D to retrieve w");
    return v[3];
}

template<size_t N>
double Vector<N>::w(void) const {
    return N > 3 ? v[3] : 0;
}

template<size_t N>
template<size_t M>
Vector<N>::operator Vector<M>() const {
    Vector<M> vec;
    auto end_i = N < M ? std::end(v) : std::next(v, M);
    std::copy(std::begin(v), end_i, std::begin(vec.v));
    return vec;
}

template<size_t N>
double Vector<N>::dot(const Vector<N>& rhs) const {
    double p = 0;
    for(size_t i = 0; i < N; i++) {
        p += v[i] * rhs.v[i];
    }
    return p;
}

template<size_t N>
double Vector<N>::norm(void) const {
    return sqrt(this->dot(*this));
}

template<size_t N>
double Vector<N>::dist(const Vector<N>& rhs) const {
    return norm(*this - rhs);
}

template<size_t N>
double Vector<N>::cos(const Vector<N>& rhs) const {
    return this->dot(rhs) / (norm() * rhs.norm());
}

template<size_t N>
double Vector<N>::angle(const Vector<N>& rhs) const {
    return acos(cos(rhs));
}

template<size_t N>
Vector<N> Vector<N>::unit(void) const {
    return *this / this->norm();
}

template<size_t N>
double& Vector<N>::operator[](const size_t rhs) {
    return v[rhs];
}

template<size_t N>
const double& Vector<N>::operator[](const size_t rhs) const {
    return v[rhs];
}

template<size_t N>
bool Vector<N>::operator==(const Vector<N>& rhs) const {
    for(size_t i = 0; i < N; i++) {
        if(abs(v[i] - rhs.v[i]) > 1e-8) {
            return false;
        }
    }
    return true;
}

template<size_t N>
bool Vector<N>::operator!=(const Vector<N>& rhs) const {
    return !(*this == rhs);
}

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

    friend Vector<N> operator*(const MatrixSlice<N>& lhs, const Matrix<N>& rhs) {
        return static_cast<Vector<N>>(lhs) * rhs;
    }

    friend std::ostream& operator<<(std::ostream& os, const MatrixSlice<N>& ms) {
        for(size_t j = 0; j < N; j++) {
            os << ms.mat.m[ms.i][j] << ' ';
        }
        os << '\n';
        return os;
    }
};

template<size_t N>
MatrixSlice<N>::MatrixSlice(Matrix<N>& mat, const size_t i) : mat(mat), i(i) {
}

template<size_t N>
double& MatrixSlice<N>::operator[](size_t j) {
    return mat.m[i][j];
}

template<size_t N>
double MatrixSlice<N>::operator[](size_t j) const {
    return mat.m[i][j];
}

template<size_t N>
MatrixSlice<N>::operator Vector<N>() const {
    Vector<N> vec;
    std::copy(std::begin(mat.m[i]), std::end(mat.m[i]), std::begin(vec.v));
    return vec;
}

template <size_t N>
struct CGUTILSSHARED_EXPORT Matrix {
    double m[N][N];

    Matrix();
    Matrix(double m[N][N]);
    template<typename T> Matrix(std::initializer_list<std::initializer_list<T>> m);
    template<size_t M> Matrix(std::initializer_list<Vector<M>> vs);
    static Matrix<N> eye(void);
    static Matrix<N> zero(void);

    Matrix<N> operator+(const Matrix<N>& rhs) const;
    Matrix<N> operator-() const;
    Matrix<N> operator+() const;
    Matrix<N> operator-(const Matrix<N>& rhs) const;
    Matrix<N> operator*(const double rhs) const;
    Matrix<N> operator*(const Matrix<N>& rhs) const;
    Matrix<N> operator/(const double rhs) const;
    MatrixSlice<N> operator[](const size_t rhs);
    bool operator==(const Matrix<N>& rhs) const;
    bool operator!=(const Matrix<N>& rhs) const;
    Matrix<N> transpose(void) const;

    friend Matrix operator*(const double lhs, const Matrix<N>& rhs) {
        return rhs * lhs;
    }

    friend Vector<N> operator*(const Vector<N>& lhs, const Matrix<N>& rhs) {
        Vector<N> vec;
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < N; j++) {
                vec[i] += lhs.v[j] * rhs.m[j][i];
            }
        }
        return vec;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& rhs) {
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < N; j++) {
                os << rhs.m[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }
};

template<size_t N>
Matrix<N>::Matrix() {
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            m[i][j] = 0;
        }
    }
}

template<size_t N>
Matrix<N>::Matrix(double m[N][N]) : m(m) {
}

template<size_t N>
template<typename T>
Matrix<N>::Matrix(std::initializer_list<std::initializer_list<T>> m) : m() {
    static_assert(std::is_convertible<T, double>::value, "Type T should be convertible to double");
    assert(m.size() > 0 && m.size() <= N);
    size_t i = 0;
    for(const auto& l: m) {
        size_t j = 0;
        assert(l.size() > 0 && l.size() <= N);
        for(const auto& k: l) {
            this->m[i][j] = static_cast<double>(k);
            j++;
        }
        i++;
    }
}

template<size_t N>
template<size_t M>
Matrix<N>::Matrix(std::initializer_list<Vector<M>> vs) : m() {
    static_assert(M <= N, "Vector size should be lesser than Matrix size");
    assert(vs.size() > 0 && vs.size() <= N);
    size_t i = 0;
    for(const auto& v: vs) {
        std::copy(std::begin(v.v), std::end(v.v), std::begin(m[i]));
        i++;
    }
}

template<size_t N>
Matrix<N> Matrix<N>::eye(void) {
    Matrix<N> mat;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] = 0;
        }
        mat.m[i][i] = 1;
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::zero(void) {
    return Matrix<N>();
}

template<size_t N>
Matrix<N> Matrix<N>::operator+(const Matrix<N>& rhs) const {
    Matrix<N> mat(*this);
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] += rhs.m[i][j];
        }
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::operator-() const {
    Matrix<N> mat(*this);
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] *= -1;
        }
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::operator+() const {
    return *this;
}

template<size_t N>
Matrix<N> Matrix<N>::operator-(const Matrix<N>& rhs) const {
    return *this + (-rhs);
}

template<size_t N>
Matrix<N> Matrix<N>::operator*(const double rhs) const {
    Matrix<N> mat(*this);
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] *= rhs;
        }
    }
    return mat;
}

template<size_t N>
Matrix<N> operator*(const double lhs, const Matrix<N>& rhs) {
    return rhs * lhs;
}

template<size_t N>
Matrix<N> Matrix<N>::operator*(const Matrix<N>& rhs) const {
    Matrix<N> mat;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            for(size_t k = 0; k < N; k++) {
                mat.m[i][j] += this->m[i][k] * rhs.m[k][j];
            }
        }
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::operator/(const double rhs) const {
    return *this * (1 / rhs);
}

template<size_t N>
MatrixSlice<N> Matrix<N>::operator[](const size_t rhs) {
    return MatrixSlice<N>(*this, rhs);
}

template<size_t N>
bool Matrix<N>::operator==(const Matrix<N>& rhs) const {
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            if(abs(m[i][j] - rhs.m[i][j]) > 1e-8) {
                return false;
            }
        }
    }
    return true;
}

template<size_t N>
Matrix<N> Matrix<N>::transpose(void) const {
    Matrix<N> mat;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat[i][j] = this->m[j][i];
        }
    }
    return mat;
}

template<size_t N>
bool Matrix<N>::operator!=(const Matrix<N>& rhs) const {
    return !(*this == rhs);
}

#endif // MATRIX_H

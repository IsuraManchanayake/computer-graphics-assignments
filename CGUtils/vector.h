#ifndef VECTOR_H
#define VECTOR_H

#include "cg-utils_global.h"

#include <ostream>
#include <cmath>
using std::sqrt;

CGUTILS_NAMESPACE_BEGIN

template<size_t N>
struct CGUTILSSHARED_EXPORT Vector {
    double v[N];
    enum { dim = N };

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
    Vector<N> cross(const Vector<N>& rhs) const;
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
    template<size_t M> operator Vector<M>() const;
    double& x(void);
    double x(void) const;
    double& y(void);
    double y(void) const;
    double& z(void);
    double z(void) const;
    double& w(void);
    double w(void) const;

    template<size_t M> friend Vector<M> CGUTILSSHARED_EXPORT operator*(const double lhs, const Vector<M>& rhs);
    template<size_t M> friend std::ostream& CGUTILSSHARED_EXPORT operator<<(std::ostream& os, const Vector<M>& rhs);
};

#include "vector.tpp"

CGUTILS_NAMESPACE_END

#endif // VECTOR_H

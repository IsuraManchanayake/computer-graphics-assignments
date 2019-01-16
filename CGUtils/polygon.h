#ifndef POLYGON_H
#define POLYGON_H

#include "triangle.h"
#include "optimalpolygontriangulator.h"

#include <vector>
#include <ostream>
using std::vector;

CGUTILS_NAMESPACE_BEGIN

struct CGUTILSSHARED_EXPORT Polygon {
    Polygon();
    template<typename TriContainer,
             typename = typename std::enable_if<is_container_of<TriContainer, Triangle>::value>::type>
        explicit Polygon(TriContainer trs);
    void print(std::ostream& os) const;
    friend CGUTILSSHARED_EXPORT std::ostream& operator<<(std::ostream& os, const Polygon& pol);
    template<typename VecContainer,
             typename = typename std::enable_if<is_container_of_vectors<VecContainer>::value>::type>
        static Polygon from_vecs(VecContainer vecs);
    template<size_t N> Polygon operator*(const Matrix<N>&) const;
    template<size_t N> Polygon& operator*=(const Matrix<N>&);

    vector<Triangle> trs;
    size_t size;

private:
    template<typename TriContainer,
             typename = typename std::enable_if<is_container_of<TriContainer, Triangle>::value>::type>
    explicit Polygon(TriContainer trs, size_t size);
};

template<typename TriContainer, typename>
Polygon::Polygon(TriContainer trs) : trs(trs.size()), size(~0ULL) {
    std::copy(std::begin(trs), std::end(trs), std::begin(this->trs));
}

template<typename TriContainer, typename>
Polygon::Polygon(TriContainer trs, size_t size) : trs(trs.size()), size(size) {
    std::copy(std::begin(trs), std::end(trs), std::begin(this->trs));
}

template<typename VecContainer, typename>
Polygon Polygon::from_vecs(VecContainer vecs) {
    return Polygon { OptimalPolygonTriangulator(vecs).compute(), vecs.size() };
}

template<size_t N>
Polygon Polygon::operator*(const Matrix<N>& mat) const {
    Polygon p(*this);
    for(auto& tr : p.trs) {
        tr *= mat;
    }
    return p;
}

template<size_t N>
Polygon& Polygon::operator*=(const Matrix<N>& mat) {
    return *this = *this * mat;
}

CGUTILS_NAMESPACE_END

#endif // POLYGON_H

#ifndef MESH_H
#define MESH_H

#include "polygon.h"

CGUTILS_NAMESPACE_BEGIN

struct CGUTILSSHARED_EXPORT Mesh {
    Mesh();
    template<typename PolygonContainer,
             typename = typename std::enable_if<is_container_of<PolygonContainer, Polygon>::value>::type>
    explicit Mesh(PolygonContainer pols);
    friend CGUTILSSHARED_EXPORT std::ostream& operator<<(std::ostream& os, const Mesh& mesh);
    template<size_t N> Mesh operator*(const Matrix<N>&) const;
    template<size_t N> Mesh& operator*=(const Matrix<N>&);

    vector<Polygon> pols;
    size_t size;
};

template<typename PolygonContainer, typename>
Mesh::Mesh(PolygonContainer pols) : pols(pols.size()), size(pols.size()) {
    std::copy(std::begin(pols), std::end(pols), std::begin(this->pols));
}

template<size_t N>
Mesh Mesh::operator*(const Matrix<N>& mat) const {
    Mesh m(*this);
    for(auto& pol : m.pols) {
        pol *= mat;
    }
    return m;
}

template<size_t N>
Mesh& Mesh::operator*=(const Matrix<N>& mat) {
    return *this = *this * mat;
}

CGUTILS_NAMESPACE_END

#endif // MESH_H

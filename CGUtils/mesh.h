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
    Mesh operator*(const Matrix<4>&) const;
    Mesh& operator*=(const Matrix<4>&);

    vector<Polygon> pols;
    size_t size;
};

template<typename PolygonContainer, typename>
Mesh::Mesh(PolygonContainer pols) : pols(pols.size()), size(pols.size()) {
    std::copy(std::begin(pols), std::end(pols), std::begin(this->pols));
}

CGUTILS_NAMESPACE_END

#endif // MESH_H

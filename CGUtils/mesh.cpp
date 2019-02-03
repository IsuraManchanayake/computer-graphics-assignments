#include "mesh.h"

CGUTILS_NAMESPACE_BEGIN

Mesh::Mesh() : size(0) {}

Mesh Mesh::operator*(const Matrix<4>& mat) const {
    Mesh m(*this);
    for(auto& pol : m.pols) {
        pol *= mat;
    }
    return m;
}

Mesh& Mesh::operator*=(const Matrix<4>& mat) {
    return *this = *this * mat;
}

std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
    os << "[Mesh: size-" << mesh.size << ' ';
    for(const auto& pol: mesh.pols) {
        pol.print(os);
    }
    return os << " ]";
}

CGUTILS_NAMESPACE_END

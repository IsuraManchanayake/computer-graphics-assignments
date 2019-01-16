#include "mesh.h"

CGUTILS_NAMESPACE_BEGIN

Mesh::Mesh() : size(0) {}

std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
    os << "[Mesh: size-" << mesh.size << ' ';
    for(const auto& pol: mesh.pols) {
        pol.print(os);
    }
    return os << " ]";
}

CGUTILS_NAMESPACE_END

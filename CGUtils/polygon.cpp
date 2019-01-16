#include "polygon.h"

CGUTILS_NAMESPACE_BEGIN

Polygon::Polygon() : size(0) {}

void Polygon::print(std::ostream& os) const {
    os << "[ ";
    for(const auto& tr: trs) {
        tr.print(os);
    }
    os << ']';
}

std::ostream& operator<<(std::ostream& os, const Polygon& pol) {
    os << "[Polygon: size-" << pol.size << ' ';
    for(const auto& tr: pol.trs) {
        tr.print(os);
    }
    return os << " ]";
}

CGUTILS_NAMESPACE_END

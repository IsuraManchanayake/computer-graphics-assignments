#include "triangle.h"

#include <algorithm>

CGUTILS_NAMESPACE_BEGIN

Triangle::Triangle() : tr() {}

void Triangle::print(std::ostream& os) const {
    os << "[ ";
    for(const auto& v: tr) {
        os << '[' << v << "] ";
    }
    os << ']';
}

std::ostream& operator<<(std::ostream& os, const Triangle& tr) {
    os << "[Triangle ";
    tr.print(os);
    return os << " ]";
}

CGUTILS_NAMESPACE_END

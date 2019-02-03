#include "triangle.h"

#include <algorithm>

CGUTILS_NAMESPACE_BEGIN

Triangle::Triangle() : tr() {}

Triangle Triangle::operator*(const Matrix<4>& mat) const {
    Triangle tr(*this);
    for(auto& v: tr.tr) {
        v *= mat;
        v = v / v.w();
    }
    return tr;
}

Triangle& Triangle::operator*=(const Matrix<4>& mat) {
    return *this = *this * mat;
}

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

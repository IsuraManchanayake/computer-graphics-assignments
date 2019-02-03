#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "matrix.h"
#include "traits.h"

#include <array>
#include <type_traits>
#include <ostream>
using std::array;

CGUTILS_NAMESPACE_BEGIN

struct CGUTILSSHARED_EXPORT Triangle {
    Triangle();
    template<typename VecContainer,
             typename = typename std::enable_if<is_container_of_vectors<VecContainer>::value>::type>
    explicit Triangle(VecContainer tr);
    friend CGUTILSSHARED_EXPORT std::ostream& operator<<(std::ostream& os, const Triangle& tr);
    void print(std::ostream& os) const;
    Triangle operator*(const Matrix<4>&) const;
    Triangle& operator*=(const Matrix<4>&);

    array<Vector<4>, 3> tr;
};

template<typename VecContainer, typename>
Triangle::Triangle(VecContainer tr) {
    if(std::remove_reference<decltype(*std::begin(tr))>::type::dim == 4) {
        std::copy(std::begin(tr), std::end(tr), std::begin(this->tr));
    } else {
        std::transform(std::begin(tr), std::distance(std::begin(tr), std::end(tr)) > 3 ? std::next(std::begin(tr), 3) : std::end(tr),
                   std::begin(this->tr), [](const auto& v) -> Vector<4> { return static_cast<Vector<4>>(v); });
    }
}

CGUTILS_NAMESPACE_END

#endif // TRIANGLE_H

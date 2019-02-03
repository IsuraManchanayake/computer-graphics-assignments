#ifndef OPTIMALPOLYGONTRIANGULATOR_H
#define OPTIMALPOLYGONTRIANGULATOR_H

#include "matrix.h"
#include "triangle.h"

#include <vector>
#include <map>
#include <utility>
using std::vector;
using std::pair;

CGUTILS_NAMESPACE_BEGIN

struct CGUTILSSHARED_EXPORT OptimalPolygonTriangulator {
    OptimalPolygonTriangulator();
    OptimalPolygonTriangulator(const vector<Vector<4>>& p);
    template<size_t N> OptimalPolygonTriangulator(const vector<Vector<N>>& p);
    vector<Triangle> compute(void);

    vector<Vector<4>> p;
private:
    pair<size_t, double> compute_core(size_t i, size_t j);
    void tr_structure(vector<Triangle>& trs, size_t i, size_t j);
    static double tr_cost(const Vector<4>& v1, const Vector<4>& v2, const Vector<4>& v3);

    std::map<pair<size_t, size_t>, pair<size_t, double>> mem;
};

template<size_t N>
OptimalPolygonTriangulator::OptimalPolygonTriangulator(const vector<Vector<N>>& p) : p(p.size()) {
        std::transform(std::begin(p), std::end(p),
                   std::begin(this->p), [](const auto& v) -> Vector<4> { return static_cast<Vector<4>>(v); });
}

CGUTILS_NAMESPACE_END

#endif // OPTIMALPOLYGONTRIANGULATOR_H

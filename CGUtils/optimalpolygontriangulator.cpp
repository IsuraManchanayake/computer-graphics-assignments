#include "optimalpolygontriangulator.h"

#include <limits>
using std::make_pair;
using std::numeric_limits;

CGUTILS_NAMESPACE_BEGIN

OptimalPolygonTriangulator::OptimalPolygonTriangulator() {}

OptimalPolygonTriangulator::OptimalPolygonTriangulator(const vector<Vector<4>>& p) : p(p) {
}

vector<Triangle> OptimalPolygonTriangulator::compute(void) {
    (void) compute_core(0, p.size() - 1);
    vector<Triangle> trs;
    tr_structure(trs, 0, p.size() - 1);
    return trs;
}

void OptimalPolygonTriangulator::tr_structure(vector<Triangle>& trs, size_t i, size_t j) {
    if(i + 1 < j) {
        size_t k = mem[make_pair(i, j)].first;
        trs.emplace_back(vector<Vector<4>>{p[i], p[j], p[k]});
        tr_structure(trs, i, k);
        tr_structure(trs, k, j);
    }
}

pair<size_t, double> OptimalPolygonTriangulator::compute_core(size_t i, size_t j) {
    auto ij = make_pair(i, j);
    if(mem.find(ij) != mem.end()) {
        return mem[ij];
    }
    if(i + 1 >= j) {
        mem[ij] = make_pair(i, 0.0);
        return mem[ij];
    }
    auto min_res = make_pair(0, numeric_limits<double>::max());
    for(size_t k = i + 1; k != j; k = (k + 1) % p.size()) {
        auto left_cost = compute_core(i, k);
        auto right_cost = compute_core(k, j);
        double tr_cost = OptimalPolygonTriangulator::tr_cost(p[i], p[j], p[k]);
        double cost = left_cost.second + right_cost.second + tr_cost;
        if(cost < min_res.second) {
            min_res = make_pair(k, cost);
        }
    }
    mem[ij] = min_res;
    return mem[ij];
}

double OptimalPolygonTriangulator::tr_cost(const Vector<4> &v1, const Vector<4> &v2, const Vector<4> &v3) {
    return v1.dist(v2) + v2.dist(v3) + v3.dist(v1);
}

CGUTILS_NAMESPACE_END

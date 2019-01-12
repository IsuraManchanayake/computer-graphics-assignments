#ifndef UTILS_IMPL_H
#define UTILS_IMPL_H

#include "utils.h"
#include <cstddef>

//template<size_t N>
//CGUTILSSHARED_EXPORT QPointF vec_to_qpointf(const Vector<N>& vec) {
//    return QPointF(vec.x(), vec.y());
//}

//template<size_t N>
//CGUTILSSHARED_EXPORT vector<QPointF> vecs_to_qpointfs(const vector<Vector<N>>& vecs) {
//    vector<QPointF> qpointfs(vecs.size());
//    std::transform(std::begin(vecs), std::end(vecs),
//                   std::begin(qpointfs), &vec_to_qpointf<N>);
//    return qpointfs;
//}

//template<size_t N>
//CGUTILSSHARED_EXPORT void draw_lines(QPainter* painter, const vector<Vector<N>>& vecs) {
//    draw_lines(painter, vecs_to_qpointfs(vecs));
//}

#endif // UTILS_IMPL_H

#ifndef UTIL_H
#define UTIL_H

#include <QWidget>
#include <QtGui>

#include <vector>
#include <algorithm>
#include <type_traits>

#include "matrix.h"
#include "mesh.h"
#include "polygon.h"
#include "triangle.h"
#include "cg-utils_global.h"

using std::vector;

CGUTILS_NAMESPACE_BEGIN

const double _r_3 = sqrt(3);

CGUTILSSHARED_EXPORT QPainter* init_painter(QWidget*);
CGUTILSSHARED_EXPORT void draw_lines(QPainter*, const vector<QPointF>&, bool flipped = true);
CGUTILSSHARED_EXPORT void draw_shape(QPainter*, const vector<QPointF>&, bool flipped = true);

template<size_t N>
QPointF vec_to_qpointf(const Vector<N>& vec) {
    return QPointF(vec.x(), vec.y());
}

template<size_t N>
vector<QPointF> vecs_to_qpointfs(const vector<Vector<N>>& vecs) {
    vector<QPointF> qpointfs(vecs.size());
    std::transform(std::begin(vecs), std::end(vecs),
                   std::begin(qpointfs), &vec_to_qpointf<N>);
    return qpointfs;
}

template<typename InputIt,
         size_t N = std::iterator_traits<InputIt>::value_type::dim,
         typename std::enable_if<
             is_vector<
                 typename std::remove_cv<typename std::iterator_traits<InputIt>::value_type>::type
                 >::value,
             int>::type = 0>
vector<QPointF> vecs_to_qpointfs(InputIt first, InputIt last) {
    vector<QPointF> qpointfs(std::distance(first, last));
    std::transform(first, last,
                   std::begin(qpointfs), &vec_to_qpointf<N>);
    return qpointfs;
}

template<size_t N>
void draw_lines(QPainter* painter, const vector<Vector<N>>& vecs) {
    draw_lines(painter, vecs_to_qpointfs(vecs));
}

template<size_t N>
void draw_shape(QPainter* painter, const vector<Vector<N>>& vecs) {
    draw_shape(painter, vecs_to_qpointfs(vecs));
}

template<typename InputIt>
void draw_shape(QPainter* painter, InputIt first, InputIt last) {
    draw_shape(painter, vecs_to_qpointfs(first, last));
}

QPointF CGUTILSSHARED_EXPORT flip_y(QPainter* painter, const QPointF& point);
void CGUTILSSHARED_EXPORT draw_flipped_line(QPainter* painter, const QPointF& p1, const QPointF& p2);

void CGUTILSSHARED_EXPORT draw_wireframe(QPainter*, const Triangle&);
void CGUTILSSHARED_EXPORT draw_wireframe(QPainter*, const Polygon&);
void CGUTILSSHARED_EXPORT draw_wireframe(QPainter*, const Mesh&);

Matrix<4> CGUTILSSHARED_EXPORT translation_mat(double x, double y, double z);
Matrix<4> CGUTILSSHARED_EXPORT scale_mat(double x, double y, double z);
Matrix<4> CGUTILSSHARED_EXPORT scale_mat(double f);
Matrix<4> CGUTILSSHARED_EXPORT rotation_mat(const Vector<4>& axis, double angle);

CGUTILSSHARED_EXPORT double map(double, double, double, double, double);
CGUTILSSHARED_EXPORT double rand_double(double x, double y);
CGUTILSSHARED_EXPORT int rand_int(int x, int y);

CGUTILSSHARED_EXPORT double dist(const QPointF&);
CGUTILSSHARED_EXPORT double dist(const QPointF&, const QPointF&);
CGUTILSSHARED_EXPORT QPointF rotate_vec2(const QPointF&, double angle);
CGUTILSSHARED_EXPORT QPointF ratio(const QPointF&, const QPointF&, double, double);

CGUTILS_NAMESPACE_END

#endif // UTIL_H

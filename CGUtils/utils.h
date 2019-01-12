#ifndef UTIL_H
#define UTIL_H

#include <QWidget>
#include <QtGui>
#include <vector>

#include "matrix.h"
#include "cg-utils_global.h"

using std::vector;

const double _r_3 = sqrt(3);

CGUTILSSHARED_EXPORT QPainter* init_painter(QWidget*);
CGUTILSSHARED_EXPORT void draw_lines(QPainter*, const vector<QPointF>&);

//template<size_t N>
//CGUTILSSHARED_EXPORT QPointF vec_to_qpointf(const Vector<N>& vec);
//template<size_t N>
//CGUTILSSHARED_EXPORT vector<QPointF> vecs_to_qpointfs(const vector<Vector<N>>& vecs);
//template<size_t N>
//CGUTILSSHARED_EXPORT void draw_lines(QPainter* painter, const vector<Vector<N>>& vecs);

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

template<size_t N>
void draw_lines(QPainter* painter, const vector<Vector<N>>& vecs) {
    draw_lines(painter, vecs_to_qpointfs(vecs));
}

CGUTILSSHARED_EXPORT double map(double, double, double, double, double);
CGUTILSSHARED_EXPORT double rand_double(double x, double y);
CGUTILSSHARED_EXPORT int rand_int(int x, int y);

CGUTILSSHARED_EXPORT double dist(const QPointF&);
CGUTILSSHARED_EXPORT double dist(const QPointF&, const QPointF&);
CGUTILSSHARED_EXPORT QPointF rotate_vec2(const QPointF&, double angle);
CGUTILSSHARED_EXPORT QPointF ratio(const QPointF&, const QPointF&, double, double);

#endif // UTIL_H

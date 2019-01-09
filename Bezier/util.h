#ifndef UTIL_H
#define UTIL_H

#include <QWidget>
#include <QtGui>
#include <vector>

#include "../Matrix/matrix.h"
#include <algorithm>

using std::vector;

const double _r_3 = sqrt(3);

QPainter* init_painter(QWidget*);
void draw_lines(QPainter*, const vector<QPointF>&);

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

double map(double, double, double, double, double);
double rand_double(double x, double y);
int rand_int(int x, int y);

double dist(const QPointF&);
double dist(const QPointF&, const QPointF&);
QPointF rotate_vec2(const QPointF&, double angle);
QPointF ratio(const QPointF&, const QPointF&, double, double);

#endif // UTIL_H

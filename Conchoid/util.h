#ifndef UTIL_H
#define UTIL_H

#include <QWidget>
#include <QtGui>

#include <vector>

using std::vector;

const double _r_3 = sqrt(3);

QPainter* init_painter(QWidget*);
double dist(const QPointF&);
void draw_lines(QPainter*, const vector<QPointF>&);
QPointF rotate_vec2(const QPointF&, double angle);
double map(double, double, double, double, double);

#endif // UTIL_H

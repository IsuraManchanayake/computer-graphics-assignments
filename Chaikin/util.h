#ifndef UTIL_H
#define UTIL_H

#include <QWidget>
#include <QtGui>

#include <vector>

using std::vector;

const double _r_3 = sqrt(3);

QPainter* init_painter(QWidget*);
void draw_lines(QPainter*, const vector<QPointF>&);

double map(double, double, double, double, double);
double rand_double(double x, double y);
int rand_int(int x, int y);

double dist(const QPointF&);
double dist(const QPointF&, const QPointF&);
QPointF rotate_vec2(const QPointF&, double angle);
QPointF ratio(const QPointF&, const QPointF&, double, double);

#endif // UTIL_H

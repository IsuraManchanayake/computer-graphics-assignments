#include "utils.h"

#include <vector>
#include <cmath>
#include <algorithm>

#include <QRandomGenerator>

using std::vector;

CGUTILS_NAMESPACE_BEGIN

QPainter* init_painter(QWidget* w) {
    QPainter* painter = new QPainter(w);
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    return painter;
}

double dist(const QPointF& p) {
    return sqrt(p.x() * p.x() + p.y() * p.y());
}

double dist(const QPointF& p, const QPointF& q) {
    return dist(p - q);
}

double rand_double(double x, double y) {
    return QRandomGenerator::global()->bounded(y - x) + x;
}

int rand_int(int x, int y) {
    return QRandomGenerator::global()->bounded(x, y);
}

QPointF flip_y(QPainter* painter, const QPointF& point) {
    return QPointF(point.x(), painter->window().height() - point.y());
}

void draw_flipped_line(QPainter* painter, const QPointF& p1, const QPointF& p2) {
    painter->drawLine(flip_y(painter, p1), flip_y(painter, p2));
}

void draw_lines(QPainter* painter, const vector<QPointF>& c, bool flipped) {
    painter->setPen(QPen(Qt::black, 2));
    int fh, fs, fl, th, ts, tl;
    fh = QRandomGenerator::global()->bounded(0, 180);
    th = QRandomGenerator::global()->bounded(180, 360);
    fs = QRandomGenerator::global()->bounded(140, 200);
    ts = QRandomGenerator::global()->bounded(140, 200);
    fl = QRandomGenerator::global()->bounded(100, 140);
    tl = QRandomGenerator::global()->bounded(100, 140);
    for(size_t i = 1; i < c.size(); i++) {
//        int h = static_cast<int>(fh + ((i - 1.0) / (c.size() - 1)) * (th - fh));
//        int s = static_cast<int>(fs + ((i - 1.0) / (c.size() - 1)) * (ts - fs));
//        int l = static_cast<int>(fl + ((i - 1.0) / (c.size() - 1)) * (tl - fl));
        int h = static_cast<int>(fh + (2.0 * (th - fh)) / (c.size() - 1) * ((i - 1 > (c.size() - 1) / 2) ? (c.size() - 1 - i) : (i - 1)));
        int s = static_cast<int>(fs + (2.0 * (ts - fs)) / (c.size() - 1) * ((i - 1 > (c.size() - 1) / 2) ? (c.size() - 1 - i) : (i - 1)));
        int l = static_cast<int>(fl + (2.0 * (tl - fl)) / (c.size() - 1) * ((i - 1 > (c.size() - 1) / 2) ? (c.size() - 1 - i) : (i - 1)));

        painter->setPen(QPen(QColor::fromHsl(h, s, l), 2));
        if(flipped) {
            draw_flipped_line(painter, c[i - 1], c[i]);
        } else {
            painter->drawLine(c[i - 1], c[i]);
        }
    }
}

void draw_wireframe(QPainter* painter, const Triangle& tr) {
    draw_shape(painter, std::begin(tr.tr), std::end(tr.tr));
}

void draw_wireframe(QPainter* painter, const Polygon& pol) {
    for(const auto& tr : pol.trs) {
        draw_wireframe(painter, tr);
    }
}

void draw_wireframe(QPainter* painter, const Mesh& mesh) {
    for(const auto& pol: mesh.pols) {
        draw_wireframe(painter, pol);
    }
}

void draw_shape(QPainter* painter, const vector<QPointF>& c, bool flipped) {
    for(size_t i = 0; i < c.size(); i++) {
        const QPointF& p1 = c[i];
        const QPointF& p2 = c[(i + 1) % c.size()];
        if(flipped) {
            draw_flipped_line(painter, p1, p2);
        } else {
            painter->drawLine(p1, p2);
        }
    }
}

Matrix<4> translation_mat(double x, double y, double z) {
    return Matrix<4>::traslation_mat({x, y, z, 1.0});
}

Matrix<4> scale_mat(double x, double y, double z) {
    return Matrix<4>::scale_mat({x, y, z, 1.0});
}

Matrix<4> scale_mat(double f) {
    return scale_mat(f, f, f);
}

//Matrix<4> rotation_mat(const Vector<4>& axis, double angle) {

//}

QPointF rotate_vec2(const QPointF& v, double t) {
    return QPointF(v.x() * cos(t) - v.y() * sin(t), v.x() * sin(t) + v.y() * cos(t));
}

double map(double x, double a, double b, double p, double q) {
    return p + ((x - a) / (b - a)) * (q - p);
}

QPointF ratio(const QPointF& p1, const QPointF& p2, double m, double n) {
    return (p1 * m + p2 * n) / (m + n);
}

CGUTILS_NAMESPACE_END

#include "util.h"

#include <vector>
#include <cmath>

#include <QRandomGenerator>

using std::vector;

QPainter* init_painter(QWidget* w) {
    QPainter* painter = new QPainter(w);
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    return painter;
}

double dist(const QPointF& p) {
    return sqrt(p.x() * p.x() + p.y() * p.y());
}

void draw_lines(QPainter* painter, const vector<QPointF>& c) {
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
        painter->drawLine(c[i - 1], c[i]);
    }
}

QPointF rotate_vec2(const QPointF& v, double t) {
    return QPointF(v.x() * cos(t) - v.y() * sin(t), v.x() * sin(t) + v.y() * cos(t));
}

double map(double x, double a, double b, double p, double q) {
    return p + ((x - a) / (b - a)) * (q - p);
}

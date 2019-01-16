#include <cmath>

#include "sierpinskisquare.h"
#include "ui_sierpinskisquare.h"
#include "utils.h"
using namespace cgutils;

SierpinskiSquare::SierpinskiSquare(QWidget *parent) :
    QMainWindow(parent),
    max_iter(1),
    ui(new Ui::SierpinskiSquare) {
    ui->setupUi(this);
}

SierpinskiSquare::~SierpinskiSquare() {
    delete ui;
}

void SierpinskiSquare::square_next_iter(void) {
    vector<QPointF>& c = cs.back();
    vector<QPointF> new_c;
    double d = static_cast<double>(this->d) / (1LL << cs.size());
    for(size_t i = 1; i < c.size(); i++) {
        QPointF& p1 = c[i - 1];
        QPointF& p2 = c[i];
        QPointF u = (p2 - p1) / dist(p1 - p2);
        vector<QPointF> tc(4);
        if(fabs(u.x()) <= 1e-8 || fabs(u.y()) <= 1e-8) {
            QPointF v = rotate_vec2(u, M_PI / 2);
            tc[0] = p1 + d * v;
            tc[1] = tc[0] + d * u + d * v;
            tc[2] = tc[1] + 2 * d * u;
            tc[3] = tc[2] + d * u - d * v;
        } else {
            QPointF v = rotate_vec2(u, -M_PI / 4);
            QPointF w = rotate_vec2(u, M_PI / 4);
            tc[0] = p1 + d * v;
            tc[1] = tc[0] + d * v - d * w;
            tc[2] = tc[0] + 2 * d * v;
            tc[3] = tc[1] + 2 * d * w;
        }
        new_c.insert(new_c.end(), tc.begin(), tc.end());
    }
    new_c.push_back(new_c.front());
    cs.push_back(new_c);
}

void SierpinskiSquare::init_curve(void) {
    QPointF R(4 * d, 0);
    QPointF U(0, -4 * d);
    QPointF r(d, 0);
    QPointF u(0, -d);

    double p = 210;
    double q = 500;
    QPointF q1(p, q);
    QPointF q2 = q1 + U;
    QPointF q3 = q2 + R;
    QPointF q4 = q3 - U;

    vector<QPointF> c = {
        q1 + r, q1 - u, q1 - r, q1 + u,
        q2 - u, q2 - r, q2 + u, q2 + r,
        q3 - r, q3 + u, q3 + r, q3 - u,
        q4 + u, q4 + r, q4 - u, q4 - r,
        q1 + r
    };
    cs.clear();
    cs.push_back(c);
}

void SierpinskiSquare::compute_curve(void) {
    if(cs.size() < max_iter) {
        if(cs.size() == 0) {
            init_curve();
        }
        while(cs.size() < max_iter) {
            square_next_iter();
        }
    }
}

void SierpinskiSquare::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);
    compute_curve();
    draw_lines(painter, cs[max_iter - 1], false);
    delete painter;
}

void SierpinskiSquare::on_horizontalSlider_valueChanged(int value) {
    max_iter = static_cast<size_t>(value);
    compute_curve();
    repaint();
}

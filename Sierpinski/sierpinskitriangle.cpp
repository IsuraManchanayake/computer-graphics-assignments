#include <cmath>

#include "sierpinskitriangle.h"
#include "ui_sierpinskitriangle.h"
#include "utils.h"

SierpinskiTriangle::SierpinskiTriangle(QWidget *parent) :
    QMainWindow(parent),
    max_iter(1),
    ui(new Ui::SierpinskiTriangle) {
    ui->setupUi(this);
}

SierpinskiTriangle::~SierpinskiTriangle() {
    delete ui;
}

void SierpinskiTriangle::next_iter(void) {
    vector<QPointF>& c = cs.back();
    vector<QPointF> new_c;
    double f = cs.size() % 2 == 0 ? 1 : -1;
    for(size_t i = 1; i < c.size(); i++, f = -f) {
        QPointF& p1 = c[i - 1];
        QPointF& p2 = c[i];
        new_c.push_back(p1);

        double d = dist(p2 - p1);
        QPointF u = (p2 - p1) / d;
        QPointF v = f * QPointF(p1.y() - p2.y(), p2.x() - p1.x()) / d;

        QPointF p1_ = p1 + (d / 4) * (_r_3 * v + u);
        QPointF p2_ = p1_ + (d / 2) * u;

        new_c.push_back(p1_);
        new_c.push_back(p2_);
    }
    new_c.push_back(c.back());
    cs.push_back(new_c);
}

void SierpinskiTriangle::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);
    if(cs.size() < max_iter) {
//        qDebug() << "Filling";
//        cs.clear();
        if(cs.size() == 0) {
            cs.push_back(vector<QPointF>{QPointF(100, 500), QPointF(600, 500)});
        }
        while(cs.size() < max_iter) {
            next_iter();
        }
    }
    draw_lines(painter, cs[max_iter - 1]);
    delete painter;
}

void SierpinskiTriangle::on_horizontalSlider_valueChanged(int value) {
    max_iter = static_cast<size_t>(value);
    repaint();
}

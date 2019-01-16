#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "utils.h"
using namespace cgutils;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    max_iter(1) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::draw_lines(const vector<QPointF> prev, const vector<QPointF>& c, QPainter* painter) {
    painter->setPen(QPen(QColor::fromHsl(0, 0, 120), 1));
    for(size_t i = 1; i < prev.size(); i++) {
        painter->drawLine(prev[i - 1], prev[i]);
    }
    painter->setPen(QPen(QColor::fromHsl(0, 0, 120), 2));
    for(size_t i = 0; i < prev.size(); i++) {
        painter->drawPoint(prev[i]);
    }
    painter->setPen(QPen(Qt::black, 1));
    for(size_t i = 1; i < c.size(); i++) {
        painter->drawLine(c[i - 1], c[i]);
    }
    painter->setPen(QPen(Qt::black, 2));
    for(size_t i = 0; i < c.size(); i++) {
        painter->drawPoint(c[i]);
    }
}

void MainWindow::init_curve(void) {
    vector<QPointF> c;
    int cnt = 0;
    while(true) {
        start: {}
        cnt++;
        for(size_t i = 0; i < 6; i++) {
            c.push_back(QPointF(rand_int(100, 600), rand_int(100, 600)));
        }
        for(size_t i = 0; i < c.size(); i++) {
            for(size_t j = i + 1; j < c.size(); j++) {
                double dx = abs(c[i].x() - c[j].x());
                double dy = abs(c[i].y() - c[j].y());
                if(dx < 50 || dy < 50) {
                    c.clear();
                    goto start;
                }
            }
        }
        break;
    }
    qDebug() << cnt << " tries";
    cs.clear();
    cs.push_back(c);
}

void MainWindow::next_iter(void) {
    vector<QPointF> new_c;
    vector<QPointF>& c = cs[cs.size() - 1];
    for(size_t i = 1; i < c.size(); i++) {
        new_c.push_back(ratio(c[i - 1], c[i], 3, 1));
        new_c.push_back(ratio(c[i - 1], c[i], 1, 3));
    }
    cs.push_back(new_c);
}

void MainWindow::compute_curve(void) {
    if(cs.size() < max_iter) {
        if(cs.size() == 0) {
            init_curve();
        }
        while(cs.size() < max_iter) {
            next_iter();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);
    compute_curve();
    draw_lines(max_iter == 1 ? vector<QPointF>() : cs[max_iter - 2], cs[max_iter - 1], painter);
    delete painter;
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
    max_iter = static_cast<size_t>(value);
    repaint();
}

void MainWindow::on_pushButton_clicked() {
    cs.clear();
    repaint();
}

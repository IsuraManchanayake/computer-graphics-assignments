#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "util.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);
    painter->setPen(QPen(QColor::fromHsl(static_cast<int>(((k + 2) / 4.0) * 359), 200, 128), 1));
    for(double t = 0.0; t < 2 * M_PI; t += 0.001) {
        double r = 1 + k * (1 / cos(t));
        double x = r * cos(t);
        double y = r * sin(t);
        double i = ((x + 4) / 8.0) * 400.0 + 100.0;
        double j = ((y + 4) / 8.0) * 400.0 + 100.0;
        if(i > 100 && i < 500 && j > 100 && j < 500) {
            painter->drawPoint(QPointF(i, j));
        }
    }
    delete painter;
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
    k = 4 * ((value / 99.0) - 0.5);
    ui->label_k_value->setNum(k);
    repaint();
}

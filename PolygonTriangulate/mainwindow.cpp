#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "utils.h"
#include "triangle.h"
#include "optimalpolygontriangulator.h"
using namespace cgutils;

#include <iostream>
using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init_polygon(void) {
    vector<VectorBase<2>> c;
    c.push_back(VectorBase<2>({200, 200}));
    c.push_back(VectorBase<2>({150, 250}));

    for(size_t i = 2; i < 10; i++) {
        VectorBase<2> curr_v = (c[i - 1] - c[i - 2]).unit();
        double t = -(M_PI / 180) * rand_double(30, 42);
        Matrix<2> rotation({{cos(t), sin(t)}, {-sin(t), cos(t)}});
        VectorBase<2> new_side = curr_v * rand_double(60, 90) * rotation;
        c.push_back(c[i - 1] + new_side);
    }
    pol = Polygon::from_vecs(c);
    cout << pol << endl;
//    pol.print(cout);
//    c = {
//        Vector<2>({150, 350}),
//        Vector<2>({200, 200}),
//        Vector<2>({250, 330}),
//        Vector<2>({300, 200}),
//        Vector<2>({350, 350})
//    };
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);

    if(pol.size == 0) {
        init_polygon();
    }
    draw_wireframe(painter, pol);

    delete painter;
}

void MainWindow::on_pushButton_pressed() {
    pol = cgutils::Polygon();
    repaint();
}

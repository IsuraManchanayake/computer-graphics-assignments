#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

#include "utils.h"
#include "polygon.h"
#include "matrix.h"
using namespace cgutils;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    vector<Vector<4>> v;
    Polygon::from_vecs(vector<Vector<4>>{Vector<4>()});
    auto p1 = Polygon::from_vecs(vector<Vector<4>>{{0, 0, 0, 1}, {1, 0, 0, 1}, {1, 0, 1, 1}, {0, 0, 1, 1}});
    auto p2 = Polygon::from_vecs(vector<Vector<4>>{{1, 0, 0, 1}, {1, 1, 0, 1}, {1, 1, 1, 1}, {1, 0, 1, 1}});
    auto p3 = Polygon::from_vecs(vector<Vector<4>>{{1, 1, 0, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 1}});
    auto p4 = Polygon::from_vecs(vector<Vector<4>>{{0, 1, 0, 1}, {0, 1, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}});
    auto p5 = Polygon::from_vecs(vector<Vector<4>>{{0, 0, 1, 1}, {1, 0, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}});
    auto p6 = Polygon::from_vecs(vector<Vector<4>>{{0, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 0, 1}, {0, 1, 0, 1}});
    mesh = Mesh(vector<cgutils::Polygon>{p1, p2, p3, p4, p5, p6});
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);

    auto display = mesh * Matrix<4>({{100, 0, 0, 0}, {0, 100, 0, 0}, {0, 0, 100, 0}, {0, 0, 0, 1}});
    cout << display << endl << endl;
    draw_wireframe(painter, display);

    delete painter;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

#include "utils.h"
#include "polygon.h"
#include "matrix.h"
using namespace cgutils;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    camera_pos(Vector<3>({5, 5, 3})),
    camera_angle(40 * M_PI / 100),
    camera_coa(Vector<3>::zero()),
    camera_up(Vector<3>({1, -1, 0})),
    camera_n(2),
    camera_f(5) {
    ui->setupUi(this);
    camera = Camera(camera_pos, camera_angle, camera_coa, camera_up, camera_n, camera_f);
    auto p1 = Polygon::from_vecs(vector<Vector<4>>{{0, 0, 0, 1}, {1, 0, 0, 1}, {1, 0, 1, 1}, {0, 0, 1, 1}});
    auto p2 = Polygon::from_vecs(vector<Vector<4>>{{1, 0, 0, 1}, {1, 1, 0, 1}, {1, 1, 1, 1}, {1, 0, 1, 1}});
    auto p3 = Polygon::from_vecs(vector<Vector<4>>{{1, 1, 0, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 1}});
    auto p4 = Polygon::from_vecs(vector<Vector<4>>{{0, 1, 0, 1}, {0, 1, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}});
    auto p5 = Polygon::from_vecs(vector<Vector<4>>{{0, 0, 1, 1}, {1, 0, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}});
    auto p6 = Polygon::from_vecs(vector<Vector<4>>{{0, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 0, 1}, {0, 1, 0, 1}});
    mesh1 = Mesh(vector<cgutils::Polygon>{p1, p2, p3, p4, p5, p6});
    mesh2 = mesh1 * translation_mat(-2.0, 3.0, 0.0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);

    cout << "camera " << camera.viewing_transform << endl << endl;
    auto display1 = mesh1 * camera.viewing_transform;
    auto display2 = mesh2 * camera.viewing_transform;

//    cout << (display * scale_mat(-200)) << endl << endl;
//    cout << scale_mat(-100) << endl << endl;
    draw_wireframe(painter, display1 * scale_mat(-100));
    draw_wireframe(painter, display2 * scale_mat(-100));

    delete painter;
}

void MainWindow::on_posxslider_valueChanged(int value) {
    camera_pos.x() = value / 10.0;
    camera.set_pos(camera_pos);
    ui->posxvaluelabel->setNum(value / 10.0);
    repaint();
}

void MainWindow::on_posyslider_valueChanged(int value) {
    camera_pos.y() = value / 10.0;
    camera.set_pos(camera_pos);
    ui->posyvaluelabel->setNum(value / 10.0);
    repaint();
}

void MainWindow::on_poszslider_valueChanged(int value) {
    camera_pos.z() = value / 10.0;
    camera.set_pos(camera_pos);
    ui->poszvaluelabel->setNum(value / 10.0);
    repaint();
}

void MainWindow::on_upxslider_valueChanged(int value) {
    camera_up.x() = value / 100.0;
    camera.set_up(camera_up);
    ui->upxvaluelabel->setNum(value / 100.0);
    repaint();
}

void MainWindow::on_upyslider_valueChanged(int value) {
    camera_up.y() = value / 100.0;
    camera.set_up(camera_up);
    ui->upyvaluelabel->setNum(value / 100.0);
    repaint();
}

void MainWindow::on_upzslider_valueChanged(int value) {
    camera_up.z() = value / 100.0;
    camera.set_up(camera_up);
    ui->upzvaluelabel->setNum(value / 100.0);
    repaint();
}

void MainWindow::on_angleslider_valueChanged(int value) {
    camera_angle = value * M_PI / 180;
    camera.set_angle(camera_angle);
    repaint();
}

void MainWindow::on_nearslider_valueChanged(int value) {
    camera_n = value / 10.0;
    camera.set_n(camera_n);
    ui->nearvaluelabel->setNum(value / 10.0);
    repaint();
}

void MainWindow::on_farslider_valueChanged(int value) {
    camera_f = value / 10.0;
    camera.set_f(camera_f);
    ui->farvaluelabel->setNum(value / 10.0);
    repaint();
}

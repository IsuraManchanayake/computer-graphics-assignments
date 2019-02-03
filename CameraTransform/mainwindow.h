#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mesh.h"
#include "camera.h"
using namespace cgutils;

#include <vector>
using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent*);
private slots:
    void on_posxslider_valueChanged(int value);
    void on_posyslider_valueChanged(int value);
    void on_poszslider_valueChanged(int value);
    void on_upxslider_valueChanged(int value);
    void on_upyslider_valueChanged(int value);
    void on_upzslider_valueChanged(int value);
    void on_angleslider_valueChanged(int value);
    void on_nearslider_valueChanged(int value);
    void on_farslider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Mesh mesh1;
    Mesh mesh2;
    Camera camera;

    Vector<3> camera_pos;
    double camera_angle;
    Vector<3> camera_coa;
    Vector<3> camera_up;
    double camera_n;
    double camera_f;
};

#endif // MAINWINDOW_H

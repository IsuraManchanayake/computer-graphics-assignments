#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "triangle.h"
#include "polygon.h"
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
    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
    Polygon pol;

    void init_polygon(void);
};

#endif // MAINWINDOW_H

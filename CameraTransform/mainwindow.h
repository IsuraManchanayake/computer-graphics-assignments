#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mesh.h"
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
private:
    Ui::MainWindow *ui;
    Mesh mesh;
};

#endif // MAINWINDOW_H

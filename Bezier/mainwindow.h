#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "../Matrix/matrix.h"

using std::vector;
using vec3 = Vector<3>;

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
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    vector<Vector<3>> points;

    void init_curve(void);
};

#endif // MAINWINDOW_H

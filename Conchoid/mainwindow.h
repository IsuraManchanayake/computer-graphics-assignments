#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    double k;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    vector<vector<QPointF>> cs; // curves
    size_t max_iter;

    void compute_curve(void);
    void init_curve(void);
    void next_iter(void);
    void draw_lines(const vector<QPointF>, const vector<QPointF>&, QPainter*);
};

#endif // MAINWINDOW_H

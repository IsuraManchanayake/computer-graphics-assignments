#ifndef SIERPINSKITRIANGLE_H
#define SIERPINSKITRIANGLE_H

#include <vector>

#include <QMainWindow>

using std::vector;

namespace Ui {
class SierpinskiTriangle;
}

class SierpinskiTriangle : public QMainWindow
{
    Q_OBJECT

    vector<vector<QPointF>> cs;
    size_t max_iter = 8;
public:
    explicit SierpinskiTriangle(QWidget *parent = nullptr);
    ~SierpinskiTriangle();
protected:
    void paintEvent(QPaintEvent*);
private slots:
    void on_horizontalSlider_valueChanged(int value);
    void next_iter(void);
private:
    Ui::SierpinskiTriangle *ui;
};

#endif // SIERPINSKITRIANGLE_H

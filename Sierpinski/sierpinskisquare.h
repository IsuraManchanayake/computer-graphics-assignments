#ifndef SIERPINSKISQUARE_H
#define SIERPINSKISQUARE_H

#include <vector>

#include <QMainWindow>

using std::vector;

namespace Ui {
class SierpinskiSquare;
}

class SierpinskiSquare : public QMainWindow
{
    Q_OBJECT

    vector<vector<QPointF>> cs;
    size_t max_iter = 8;
    int d = 70;
public:
    explicit SierpinskiSquare(QWidget *parent = nullptr);
    ~SierpinskiSquare();
protected:
    void paintEvent(QPaintEvent*);
private slots:
    void on_horizontalSlider_valueChanged(int value);
    void square_next_iter(void);
    void init_curve(void);
    void compute_curve(void);
private:
    Ui::SierpinskiSquare *ui;
};

#endif // SIERPINSKISQUARE_H

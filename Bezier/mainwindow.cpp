#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "utils.h"
using namespace cgutils;

#include <vector>

using std::vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init_curve(void) {
    points.clear();
    vector<VectorBase<3>>& ps = points;
    int cnt = 0;
    while(true) {
        start: {}
        cnt++;
        size_t num_curves = 2;
        for(size_t i = 0; i < 3 * num_curves + 1; i++) {
            ps.push_back(VectorBase<3>({rand_int(100, 600), rand_int(100, 600), 1}));
        }
//        for(size_t i = 0; i < ps.size(); i++) {
//            for(size_t j = i + 1; j < ps.size(); j++) {
//                double dx = abs(ps[i].x() - ps[j].x());
//                double dy = abs(ps[i].y() - ps[j].y());
//                if(dx < 50 || dy < 50) {
//                    ps.clear();
//                    goto start;
//                }
//            }
//        }
        for(size_t i = 1; i < ps.size() - 1; i++) {
            VectorBase<3> v1 = ps[i - 1] - ps[i];
            VectorBase<3> v2 = ps[i + 1] - ps[i];
            double angle = v1.angle(v2);
            if(angle < M_PI / 6) {
                ps.clear();
                goto start;
            }
        }
        break;
    }
    qDebug() << cnt << " tries";
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter* painter = init_painter(this);

    if(points.size() == 0) {
        init_curve();
    }

    painter->setPen(QPen(Qt::red, 1));
    for(size_t i = 1; i < points.size(); i++) {
        QPointF p1 = vec_to_qpointf(points[i - 1]);
        QPointF p2 = vec_to_qpointf(points[i]);
        painter->drawLine(p1, p2);
    }

    vector<VectorBase<4>> cp;
    for(size_t i = 3; i < points.size(); i += 3) {
        Matrix<4> pmat({points[i - 3], points[i - 2], points[i - 1], points[i]});
        const Matrix<4> bmat({{1, 0, 0, 0}, {-3, 3, 0, 0}, {3, -6, 3, 0}, {-1, 3, -3, 1}});
        for(double t = 0; t <= 1.009; t += 0.01) {
            VectorBase<4> tvec = VectorBase<4>::vec(1.0, t, t * t, t * t * t);
            VectorBase<4> outv = tvec * bmat * pmat;
            cp.push_back(outv);
        }
    }

    painter->setPen(QPen(Qt::black, 3));
    for(size_t i = 1; i < cp.size(); i++) {
        QPointF p1 = vec_to_qpointf(cp[i - 1]);
        QPointF p2 = vec_to_qpointf(cp[i]);
        painter->drawLine(p1, p2);
    }

    delete painter;
}

void MainWindow::on_pushButton_clicked() {
    points.clear();
    repaint();
}

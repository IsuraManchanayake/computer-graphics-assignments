#include "sierpinskitriangle.h"
#include "sierpinskisquare.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SierpinskiTriangle w;
//    SierpinskiSquare w;
    w.show();

    return a.exec();
}

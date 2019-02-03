#ifndef CAMERA_H
#define CAMERA_H

#include "cg-utils_global.h"
#include "vector.h"
#include "matrix.h"

CGUTILS_NAMESPACE_BEGIN

struct CGUTILSSHARED_EXPORT Camera {
    Camera();
    Camera(const Vector<3>& pos, double angle, const Vector<3>& coa, const Vector<3>& up, double n, double f);

    Vector<3> pos;
    double angle;
    Vector<3> coa;
    Vector<3> view;
    Vector<3> up;
    double n;
    double f;
    Matrix<4> viewing_transform;

    void set_pos(const Vector<3>& pos);
    void set_angle(double angle);
    void set_coa(const Vector<3>& coa);
    void set_view(const Vector<3>& view);
    void set_up(const Vector<3>& up);
    void set_n(double n);
    void set_f(double f);
    void update_matrix(void);
};

CGUTILS_NAMESPACE_END

#endif // CAMERA_H

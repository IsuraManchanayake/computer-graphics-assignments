#include "camera.h"

#include <cmath>
#include <iostream>

CGUTILS_NAMESPACE_BEGIN

Camera::Camera() {
}

Camera::Camera(const Vector<3>& pos, double angle, const Vector<3>& coa, const Vector<3>& up, double n, double f)
    : pos(pos),
      angle(angle),
      coa(coa),
      n(n),
      f(f) {
    view = (coa - pos).unit();
    this->up = view.cross(up).cross(view).unit();

    auto w = view.cross(this->up);
    auto C = Matrix<4>({
                           {w.x(), this->up.x(), -view.x(), 0.0},
                           {w.y(), this->up.y(), -view.y(), 0.0},
                           {w.z(), this->up.z(), -view.z(), 0.0},
                           {  1.0,          1.0,       1.0, 1.0}
                       })
            * Matrix<4>::traslation_mat({pos.x(), pos.y(), pos.z(), 1.0});
    viewing_transform = C * Matrix<4>({
                                     {1 / tan(angle / 2),   0.0,                0.0,                    0.0},
                                     {0.0,                  1 / tan(angle / 2), 0.0,                    0.0},
                                     {0.0,                  0.0,                (f + n) / (f - n),     -1.0},
                                     {0.0,                  0.0,                (2 * f * n) / (f - n),  0.0}
                                 });
}

void Camera::set_pos(const Vector<3>& pos) {
    view = (coa - pos).unit();
    up = view.cross(up).cross(view).unit();
    update_matrix();
}

void Camera::set_angle(double angle) {
    this->angle = angle;
    update_matrix();
}

void Camera::set_coa(const Vector<3>& coa) {
    this->coa = coa;
    view = (coa - pos).unit();
    up = view.cross(up).cross(view).unit();
    update_matrix();
}

void Camera::set_view(const Vector<3>& view) {
    this->view = view;
    coa = pos + view * coa.norm();
    up = view.cross(up).cross(view).unit();
    update_matrix();
}

void Camera::set_up(const Vector<3>& up) {
    this->up = view.cross(up).cross(view).unit();
    update_matrix();
}

void Camera::set_n(double n) {
    this->n = n;
    update_matrix();
}

void Camera::set_f(double f) {
    this->f = f;
    update_matrix();
}

void Camera::update_matrix(void) {
    auto w = view.cross(this->up);
    auto C = Matrix<4>({
                           {w.x(), this->up.x(), -view.x(), 0.0},
                           {w.y(), this->up.y(), -view.y(), 0.0},
                           {w.z(), this->up.z(), -view.z(), 0.0},
                           {  1.0,          1.0,       1.0, 1.0}
                       })
            * Matrix<4>::traslation_mat({pos.x(), pos.y(), pos.z(), 1.0});
    viewing_transform = C * Matrix<4>({
                                     {1 / tan(angle / 2),   0.0,                0.0,                    0.0},
                                     {0.0,                  1 / tan(angle / 2), 0.0,                    0.0},
                                     {0.0,                  0.0,                (f + n) / (f - n),     -1.0},
                                     {0.0,                  0.0,                (2 * f * n) / (f - n),  0.0}
                                 });
}

CGUTILS_NAMESPACE_END

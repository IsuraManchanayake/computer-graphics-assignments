#include <iostream>
#include <cassert>

#include "matrix.h"

using namespace std;

using vec4 = Vector<4>;
using mat4 = Matrix<4>;

#define test_vec(x) do { cout << #x << " == " << (x) << '\n'; } while(0)
#define test_mat(x) do { cout << #x << " => \n" << (x) << '\n'; } while(0)

void test_vector(void) {
    test_vec(vec4::one());
    test_vec(vec4::zero());
    test_vec(vec4());
    test_vec(vec4({1, 2, 3, 4}));
    test_vec(vec4::vec(3, 4));

    vec4 v1 = vec4::one();
    vec4 v2 = vec4::vec(1, 2);
    test_vec(v1);
    test_vec(v2);
    test_vec(v1 + v2);
    test_vec(v1 - v2);
    test_vec(+v1);
    test_vec(-v1);
    test_vec(v1 * 0.4);
    test_vec(0.3 * v1);
    test_vec(v1 / 4);
    test_vec(v1.dot(v2));
    test_vec(v1.norm());
    test_vec(v1.unit());
    test_vec(v1[0]);
    test_vec(v1 == vec4::one());
    test_vec(v1 != vec4::zero());

    test_vec(v1.x());
    test_vec(v1.y());
    test_vec(v1.z());
    test_vec(v1.w());

    test_vec(Vector<3>().x());
//    test_vec(Vector<3>().w()); // !Compiler Error

    v1[0] = 0;
    test_vec(v1);

    test_vec(static_cast<Vector<3>>(vec4::one()));
    test_vec(static_cast<Vector<5>>(vec4::one()));
}

void test_matrix(void) {
    cout << '\n';

    test_mat(mat4::eye());
    test_mat(mat4::zero());
    test_mat(mat4({{1, 2}, {3, 4}}));
//    test_mat(mat4({1.0, 2.0, 3.0, 4.0, 1.0, 2.0, 3.0, 4.0, 1.0, 2.0, 3.0, 4.0, 1.0, 2.0, 3.0, 4.0}));
    test_mat(mat4({{1.0, 2.0, 3.0, 4.0}, {1.0, 2.0, 3.0, 4.0}, {1.0, 2.0, 3.0, 4.0}, {1.0, 2.0, 3.0, 4.0}}));

    mat4 m1 = mat4::eye();
    mat4 m2 = mat4({{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}});
    test_mat(m1 + m2);
    test_mat(-m1);
    test_mat(+m1);
    test_mat(m1 - m2);
    test_mat(m1 * 2);
    test_mat(0.3 * m1);
    test_mat(m1 * m2);
    test_mat(m1 / 4);
    test_mat(m1[0]);
    test_mat(m1 == mat4::eye());
    test_mat(m1 != mat4::eye());

    test_mat(static_cast<vec4>(m2[0]));
    test_mat(m2[0]);
    m1[0][0] = 9;
    test_mat(m1);
    test_mat(m1[0] * m2);
    test_mat(m1 * m1 * m2);
    test_mat(m2.transpose());
    test_mat(mat4({vec4::one(), vec4::zero(), vec4::one() * 0.2}));
    test_mat(mat4({Vector<3>::one()}));
}

int main() {
    test_vector();
    test_matrix();
    return 0;
}

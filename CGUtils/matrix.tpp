template<size_t N>
MatrixSlice<N>::MatrixSlice(Matrix<N>& mat, const size_t i) : mat(mat), i(i) {
}

template<size_t N>
double& MatrixSlice<N>::operator[](size_t j) {
    return mat.m[i][j];
}

template<size_t N>
double MatrixSlice<N>::operator[](size_t j) const {
    return mat.m[i][j];
}

template<size_t N>
MatrixSlice<N>::operator Vector<N>() const {
    Vector<N> vec;
    std::copy(std::begin(mat.m[i]), std::end(mat.m[i]), std::begin(vec.v));
    return vec;
}

template<size_t N>
Vector<N> operator*(const MatrixSlice<N>& lhs, const Matrix<N>& rhs) {
    return static_cast<Vector<N>>(lhs) * rhs;
}

template<size_t N>
std::ostream& operator<<(std::ostream& os, const MatrixSlice<N>& ms) {
    for(size_t j = 0; j < N; j++) {
        os << ms.mat.m[ms.i][j] << ' ';
    }
    os << '\n';
    return os;
}

template<size_t N>
MatrixSlice<N>& MatrixSlice<N>::operator=(const Vector<N>& rhs) {
    for(size_t j = 0; j < N; j++) {
        mat.m[i][j] = rhs[j];
    }
    return *this;
}

template<size_t N>
Matrix<N>::Matrix() {
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            m[i][j] = 0;
        }
    }
}

template<size_t N>
Matrix<N>::Matrix(double m[N][N]) : m(m) {
}

template<size_t N>
template<typename T>
Matrix<N>::Matrix(std::initializer_list<std::initializer_list<T>> m) : m() {
    static_assert(std::is_convertible<T, double>::value, "Type T should be convertible to double");
    assert(m.size() > 0 && m.size() <= N);
    size_t i = 0;
    for(const auto& l: m) {
        size_t j = 0;
        assert(l.size() > 0 && l.size() <= N);
        for(const auto& k: l) {
            this->m[i][j] = static_cast<double>(k);
            j++;
        }
        i++;
    }
}

template<size_t N>
template<size_t M>
Matrix<N>::Matrix(std::initializer_list<Vector<M>> vs) : m() {
    static_assert(M <= N, "Vector size should be lesser than Matrix size");
    assert(vs.size() > 0 && vs.size() <= N);
    size_t i = 0;
    for(const auto& v: vs) {
        std::copy(std::begin(v.v), std::end(v.v), std::begin(m[i]));
        i++;
    }
}

template<size_t N>
Matrix<N> Matrix<N>::eye(void) {
    Matrix<N> mat;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] = 0;
        }
        mat.m[i][i] = 1;
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::zero(void) {
    return Matrix<N>();
}

template<size_t N>
Matrix<N> Matrix<N>::traslation_mat(const Vector<N>& trn) {
    Matrix<N> mat = Matrix<N>::eye();
    for(size_t i = 0; i < N; i++) {
        mat.m[N - 1][i] = trn.v[i];
    }
    return mat;
}

//template<size_t N>
//Matrix<N> Matrix<N>::rotation_mat(const Vector<N>& rot) {
//    Matrix<N> mat =
//}

template<size_t N>
Matrix<N> Matrix<N>::scale_mat(const Vector<N>& fac) {
    Matrix<N> mat = Matrix<N>::zero();
    for(size_t i = 0; i < N; i++) {
        mat.m[i][i] = fac.v[i];
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::scale_mat(double fac) {
    return Matrix<N>::eye() * fac;
}

template<size_t N>
Matrix<N> Matrix<N>::operator+(const Matrix<N>& rhs) const {
    Matrix<N> mat(*this);
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] += rhs.m[i][j];
        }
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::operator-() const {
    Matrix<N> mat(*this);
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] *= -1;
        }
    }
    return mat;
}

template<size_t N>
Matrix<N> Matrix<N>::operator+() const {
    return *this;
}

template<size_t N>
Matrix<N> Matrix<N>::operator-(const Matrix<N>& rhs) const {
    return *this + (-rhs);
}

template<size_t N>
Matrix<N> Matrix<N>::operator*(const double rhs) const {
    Matrix<N> mat(*this);
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat.m[i][j] *= rhs;
        }
    }
    return mat;
}

template<size_t N>
Matrix<N>& Matrix<N>::operator*=(const double rhs) {
    return *this = *this * rhs;
}

template<size_t N>
Matrix<N> Matrix<N>::operator*(const Matrix<N>& rhs) const {
    Matrix<N> mat;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            for(size_t k = 0; k < N; k++) {
                mat.m[i][j] += this->m[i][k] * rhs.m[k][j];
            }
        }
    }
    return mat;
}

template<size_t N>
Matrix<N>& Matrix<N>::operator*=(const Matrix<N>& rhs) {
    return *this = *this * rhs;
}

template<size_t N>
Matrix<N> Matrix<N>::operator/(const double rhs) const {
    return *this * (1 / rhs);
}

template<size_t N>
MatrixSlice<N> Matrix<N>::operator[](const size_t rhs) {
    return MatrixSlice<N>(*this, rhs);
}

template<size_t N>
bool Matrix<N>::operator==(const Matrix<N>& rhs) const {
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            if(abs(m[i][j] - rhs.m[i][j]) > 1e-8) {
                return false;
            }
        }
    }
    return true;
}

template<size_t N>
Matrix<N> Matrix<N>::transpose(void) const {
    Matrix<N> mat;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            mat[i][j] = this->m[j][i];
        }
    }
    return mat;
}

template<size_t N>
bool Matrix<N>::operator!=(const Matrix<N>& rhs) const {
    return !(*this == rhs);
}

template<size_t N>
Matrix<N> operator*(const double lhs, const Matrix<N>& rhs) {
    return rhs * lhs;
}

template<size_t N>
Vector<N> operator*(const Vector<N>& lhs, const Matrix<N>& rhs) {
    Vector<N> vec;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            vec[i] += lhs.v[j] * rhs.m[j][i];
        }
    }
    return vec;
}

template<size_t N>
Vector<N>& operator*=(Vector<N>& lhs, const Matrix<N>& rhs) {
    return lhs = lhs * rhs;
}

template<size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<N>& rhs) {
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            os << rhs.m[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}


template<size_t N>
Vector<N>::Vector() {
    for(size_t i = 0; i < N; i++) {
        v[i] = 0;
    }
}

template<size_t N>
Vector<N>::Vector(double v[N]) : v(v) {
}

template<size_t N>
template<typename T>
Vector<N>::Vector(const std::initializer_list<T>& v) : v() {
    static_assert(std::is_convertible<T, double>::value, "Type T should be convertible to double");
    std::transform(std::begin(v), std::end(v),
              std::begin(this->v), [](const T& e) {return static_cast<double>(e);});
}

template<size_t N>
template<typename... T>
Vector<N> Vector<N>::vec(T... vs) {
    Vector vv;
    auto vt = {vs...};
    assert(vt.size() > 0 && vt.size() <= N);
    std::copy(std::begin(vt), std::end(vt), std::begin(vv.v));
    return vv;
}

template<size_t N>
Vector<N> Vector<N>::one(void) {
    Vector<N> vec;
    for(size_t i = 0; i < N; i++) {
        vec.v[i] = 1;
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::zero(void) {
    return Vector<N>();
}

template<size_t N>
Vector<N> Vector<N>::operator+(const Vector<N>& rhs) const {
    Vector<N> vec(*this);
    for(size_t i = 0; i < N; i++) {
        vec.v[i] += rhs.v[i];
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::operator-() const {
    Vector<N> vec(*this);
    for(size_t i = 0; i < N; i++) {
        vec.v[i] *= -1;
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::operator+() const {
    return *this;
}

template<size_t N>
Vector<N> Vector<N>::operator-(const Vector<N>& rhs) const {
    return *this + (-rhs);
}

template<size_t N>
Vector<N> Vector<N>::operator*(const double rhs) const {
    Vector<N> vec(*this);
    for(size_t i = 0; i < N; i++) {
        vec.v[i] *= rhs;
    }
    return vec;
}

template<size_t N>
Vector<N> Vector<N>::operator/(const double rhs) const {
    return *this * (1 / rhs);
}

template<size_t N>
double& Vector<N>::x(void) {
    static_assert(N > 0, "Vector should be at least 1-D to retrieve x");
    return v[0];
}

template<size_t N>
double Vector<N>::x(void) const {
    return N > 0 ? v[0] : 0;
}

template<size_t N>
double& Vector<N>::y(void) {
    static_assert(N > 1, "Vector should be at least 2-D to retrieve y");
    return v[1];
}

template<size_t N>
double Vector<N>::y(void) const {
    return N > 1 ? v[1] : 0;
}

template<size_t N>
double& Vector<N>::z(void) {
    static_assert(N > 2, "Vector should be at least 3-D to retrieve z");
    return v[2];
}

template<size_t N>
double Vector<N>::z(void) const {
    return N > 2 ? v[2] : 0;
}

template<size_t N>
double& Vector<N>::w(void) {
    static_assert(N > 3, "Vector should be at least 4-D to retrieve w");
    return v[3];
}

template<size_t N>
double Vector<N>::w(void) const {
    return N > 3 ? v[3] : 0;
}

template<size_t N>
template<size_t M>
Vector<N>::operator Vector<M>() const {
    Vector<M> vec;
    auto end_i = N < M ? std::end(v) : std::next(v, M);
    std::copy(std::begin(v), end_i, std::begin(vec.v));
    return vec;
}

template<size_t N>
double Vector<N>::dot(const Vector<N>& rhs) const {
    double p = 0;
    for(size_t i = 0; i < N; i++) {
        p += v[i] * rhs.v[i];
    }
    return p;
}

template<size_t N>
double Vector<N>::norm(void) const {
    return sqrt(this->dot(*this));
}

template<size_t N>
double Vector<N>::dist(const Vector<N>& rhs) const {
    return (*this - rhs).norm();
}

template<size_t N>
double Vector<N>::cos(const Vector<N>& rhs) const {
    return this->dot(rhs) / (norm() * rhs.norm());
}

template<size_t N>
double Vector<N>::angle(const Vector<N>& rhs) const {
    return acos(cos(rhs));
}

template<size_t N>
Vector<N> Vector<N>::unit(void) const {
    return *this / this->norm();
}

template<size_t N>
double& Vector<N>::operator[](const size_t rhs) {
    return v[rhs];
}

template<size_t N>
const double& Vector<N>::operator[](const size_t rhs) const {
    return v[rhs];
}

template<size_t N>
bool Vector<N>::operator==(const Vector<N>& rhs) const {
    for(size_t i = 0; i < N; i++) {
        if(abs(v[i] - rhs.v[i]) > 1e-8) {
            return false;
        }
    }
    return true;
}

template<size_t N>
bool Vector<N>::operator!=(const Vector<N>& rhs) const {
    return !(*this == rhs);
}

template<size_t N>
Vector<N> operator*(const double lhs, const Vector<N>& rhs) {
    return rhs * lhs;
}

template<size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<N>& rhs) {
    for(size_t i = 0; i < N; i++) {
        os << rhs.v[i] << ' ';
    }
    return os;
}

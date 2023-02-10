#include "dual.h"

template<typename T>
Dual<T>::Dual(const T& real, const T& dual) : real_(real), dual_(dual) {}

/*!
 * @brief (u + v)' = u' + v'
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
template<typename T>
Dual<T> Dual<T>::operator+(const Dual& rhs) const {
    return Dual(real_ + rhs.real_, dual_ + rhs.dual_);
}

/*!
 * @brief (u - v)' = u' - v'
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
template<typename T>
Dual<T> Dual<T>::operator-(const Dual& rhs) const {
    return Dual(real_ - rhs.real_, dual_ - rhs.dual_);
}

/*!
 * @brief (uv)' = u'v + v'u
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
template<typename T>
Dual<T> Dual<T>::operator*(const Dual& rhs) const {
    return Dual(real_ * rhs.real_, real_ * rhs.dual_ + dual_ * rhs.real_);
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Dual<U>& dual) {
    os << std::setw(10) << std::right << "real_: {" << std::setw(10) << std::right << dual.real_ << std::setw(10)
       << "  }  dual_: {" << std::setw(10)
       << std::right << dual.dual_ << "  }";
    return os;
}

template<typename T>
bool Dual<T>::operator<(const Dual& rhs) const {
    return real_ < rhs.real_;
}

template<typename T>
bool Dual<T>::operator>(const Dual& rhs) const {
    return real_ > rhs.real_;
}

/*!
 * @brief (sin(x))' = cos(x) * x'
 * @param dual is the Dual object to be sine'd.
 * @return a resulting Dual object.
 */
template<typename T>
Dual<T> sin(const Dual<T>& dual) {
    using std::sin, std::cos;
    return Dual(sin(dual.real_), cos(dual.real_) * dual.dual_);
}

/*!
 * @brief (cos(x))' = -sin(x) * x'
 * @param dual is the Dual object to be cosine'd.
 * @return a resulting Dual object.
 */
template<typename T>
Dual<T> cos(const Dual<T>& dual) {
    using std::sin, std::cos;
    return Dual(cos(dual.real_), -sin(dual.real_) * dual.dual_);
}

/*!
 * @brief (exp(x))' = exp(x) * x'
 * @param dual is the Dual object to be sine'd.
 * @return a resulting Dual object.
 */
template<typename T>
Dual<T> exp(const Dual<T>& dual) {
    using std::exp;
    return Dual(exp(dual.real_), exp(dual.real_) * dual.dual_);
}

#include "dual.h"

Dual::Dual(double real, double dual) : real_(real), dual_(dual) {}

/*!
 * @brief (u + v)' = u' + v'
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
Dual Dual::operator+(const Dual& rhs) const {
    return Dual(real_ + rhs.real_, dual_ + rhs.dual_);
}

/*!
 * @brief (u - v)' = u' - v'
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
Dual Dual::operator-(const Dual& rhs) const {
    return Dual(real_ - rhs.real_, dual_ - rhs.dual_);
}

/*!
 * @brief (uv)' = u'v + v'u
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
Dual Dual::operator*(const Dual& rhs) const {
    return Dual(real_ * rhs.real_, real_ * rhs.dual_ + dual_ * rhs.real_);
}

std::ostream& operator<<(std::ostream& os, const Dual& dual) {
    os << std::setw(10) << std::right << "real_: " << std::setw(10) << std::right << dual.real_ << std::setw(10)
       << " dual_: " << std::setw(10)
       << std::right << dual.dual_;
    return os;
}

bool Dual::operator<(const Dual& rhs) const {
    return real_ < rhs.real_;
}

bool Dual::operator>(const Dual& rhs) const {
    return real_ > rhs.real_;
}

/*!
 * @brief (sin(x))' = cos(x) * x'
 * @param dual is the Dual object to be sine'd.
 * @return a resulting Dual object.
 */
Dual sin(const Dual& dual) {
    return Dual(std::sin(dual.real_), std::cos(dual.real_) * dual.dual_);
}

/*!
 * @brief (cos(x))' = -sin(x) * x'
 * @param dual is the Dual object to be cosine'd.
 * @return a resulting Dual object.
 */
Dual cos(const Dual& dual) {
    return Dual(std::cos(dual.real_), -std::sin(dual.real_) * dual.dual_);
}

/*!
 * @brief (exp(x))' = exp(x) * x'
 * @param dual is the Dual object to be sine'd.
 * @return a resulting Dual object.
 */
Dual exp(const Dual& dual) {
    return Dual(std::exp(dual.real_), std::exp(dual.real_) * dual.dual_);
}

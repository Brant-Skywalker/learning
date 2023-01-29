#include "dual.h"

Dual::Dual(double real, double dual) : _real(real), _dual(dual) {}

/*!
 * @brief (u + v)' = u' + v'
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
Dual Dual::operator+(const Dual& rhs) const {
    return Dual(_real + rhs._real, _dual + rhs._dual);
}

/*!
 * @brief (u - v)' = u' - v'
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
Dual Dual::operator-(const Dual& rhs) const {
    return Dual(_real - rhs._real, _dual - rhs._dual);
}

/*!
 * @brief (uv)' = u'v + v'u
 * @param rhs is the other Dual object.
 * @return a resulting Dual object.
 */
Dual Dual::operator*(const Dual& rhs) const {
    return Dual(_real * rhs._real, _real * rhs._dual + _dual * rhs._real);
}

std::ostream& operator<<(std::ostream& os, const Dual& dual) {
    os << "_real: " << std::setw(10) << dual._real << std::setw(10) << " _dual: " << std::setw(10) << dual._dual;
    return os;
}

/*!
 * @brief (sin(x))' = cos(x) * x'
 * @param dual is the Dual object to be sine'd.
 * @return a resulting Dual object.
 */
Dual sin(const Dual& dual) {
    return Dual(std::sin(dual._real), std::cos(dual._real) * dual._dual);
}

/*!
 * @brief (cos(x))' = -sin(x) * x'
 * @param dual is the Dual object to be cosine'd.
 * @return a resulting Dual object.
 */
Dual cos(const Dual& dual) {
    return Dual(std::cos(dual._real), -std::sin(dual._real) * dual._dual);
}

/*!
 * @brief (exp(x))' = exp(x) * x'
 * @param dual is the Dual object to be sine'd.
 * @return a resulting Dual object.
 */
Dual exp(const Dual& dual) {
    return Dual(std::exp(dual._real), std::exp(dual._real) * dual._dual);
}

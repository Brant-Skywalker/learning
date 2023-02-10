#include "zonotope.h"

template<typename T>
Zonotope<T>::Zonotope(const Interval<T>& interval) {
    x0_ = (interval.hi_ - interval.lo_) / 2. + interval.lo_;
    xi_[i_++] = x0_ - interval.lo_;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Zonotope<U>& zonotope) {
    os << std::setw(10) << std::right << "x0_: " << std::setw(10) << std::right << zonotope.x0_ << std::setw(10)
       << std::right << " xi_: " << "{  ";
    for (const auto& [k, v] : zonotope.xi_) {
        os << k << ": " << v << ", ";
    }
    os << " }";

    return os;
}

template<typename T>
Zonotope<T>::Zonotope(const T& x0, const std::unordered_map<int, T>& xi) :x0_(x0), xi_(xi) {}

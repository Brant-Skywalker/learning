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

template<typename T>
Interval<T> Zonotope<T>::getInterval() {
    T lo = x0_ - std::accumulate(xi_.begin(), xi_.end(), 0.,
                                 [](const T& prev, const auto& elem) { return prev + elem.second; });
    T hi = x0_ + std::accumulate(xi_.begin(), xi_.end(), 0.,
                                 [](const T& prev, const auto& elem) { return prev + elem.second; });
    return Interval{lo, hi};
}

template<typename T>
Zonotope<T> Zonotope<T>::operator+(const Zonotope<T>& rhs) const {
    T x0 = x0_ + rhs.x0_;
    std::unordered_map<int, T> xi{};

    for (const auto& [k, v] : xi_) {
        if (rhs.xi_.end() != rhs.xi_.find(k)) {
            if (0. != v + rhs.xi_.at(k)) {
                xi[k] = v + rhs.xi_.at(k);
            }
        } else {
            xi[k] = v;
        }
    }

    for (const auto& [k, v] : rhs.xi_) {
        if (xi_.end() != xi_.find(k)) {
            if (0. != v + xi_.at(k)) {
                xi[k] = v + xi_.at(k);
            }
        } else {
            xi[k] = v;
        }
    }

    return Zonotope{x0, xi};
}

template<typename T>
Zonotope<T> Zonotope<T>::operator*(const double rhs) const {
    std::unordered_map<int, T> xi{xi_};
    std::for_each(xi.begin(), xi.end(), [rhs](auto& it) { it.second *= rhs; });
    return Zonotope{x0_ * rhs, xi};
}

template<typename U>
Zonotope<U> operator*(const double lhs, const Zonotope<U>& rhs) {
    return rhs * lhs;
}

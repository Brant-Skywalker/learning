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

/*!
 * @brief If the largest subscript of the noise term in the input zonotope is greater than the static variable `i_`,
 * update `i_`.
 */
template<typename T>
Zonotope<T>::Zonotope(const T& x0, const std::unordered_map<int, T>& xi) :x0_(x0), xi_(xi) {
    int i = std::max_element(xi.begin(), xi.end(),
                             [](const auto& l, const auto& r) { return l.first < r.second; })->first + 1;
    i_ = i > i_ ? i : i_;
}

template<typename T>
Interval<T> Zonotope<T>::getInterval() const {
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
Zonotope<T> Zonotope<T>::operator*(const T& rhs) const {
    std::unordered_map<int, T> xi{xi_};
    std::for_each(xi.begin(), xi.end(), [rhs](auto& it) { it.second *= rhs; });
    return Zonotope{x0_ * rhs, xi};
}

template<typename U>
Zonotope<U> operator*(const U& lhs, const Zonotope<U>& rhs) {
    return rhs * lhs;
}

template<typename T>
T Zonotope<T>::getRad() const {
    using std::abs;
    return std::accumulate(xi_.begin(), xi_.end(), 0.,
                           [](const T& prev, const auto& elem) { return prev + abs(elem.second); });
}

template<typename T>
Zonotope<T> Zonotope<T>::operator*(const Zonotope& rhs) const {
    T x0 = x0_ * rhs.x0_;
    std::unordered_map<int, T> xi{};
    auto max_l = std::max_element(xi_.begin(), xi_.end(),
                                  [](const auto& l, const auto& r) { return l.first < r.second; });
    auto max_r = std::max_element(rhs.xi_.begin(), rhs.xi_.end(),
                                  [](const auto& l, const auto& r) { return l.first < r.second; });
    int max_i = std::max(max_l->first, max_r->first);

    for (int i = 1; i <= max_i; ++i) {
        auto it_l = xi_.find(i);
        auto it_r = rhs.xi_.find(i);
        T v{};
        if (xi_.end() != it_l && rhs.xi_.end() == it_r) {
            v = xi_.at(i) * rhs.x0_;
        } else if (xi_.end() == it_l && rhs.xi_.end() != it_r) {
            v = rhs.xi_.at(i) * x0_;
        } else if (xi_.end() != it_l && rhs.xi_.end() != it_r) {
            v = xi_.at(i) * rhs.x0_ + rhs.xi_.at(i) * x0_;
        }
        if (0. != v) {
            xi[i] = v;
        }
    }
    xi[i_++] = getRad() * rhs.getRad();

    return Zonotope{x0, xi};
}


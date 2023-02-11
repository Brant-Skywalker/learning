#include "affine.h"

template<typename T>
Affine<T>::Affine(const Interval<T>& interval) {
    x0_ = (interval.hi_ - interval.lo_) / 2. + interval.lo_;
    xi_[i_++] = x0_ - interval.lo_;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Affine<U>& affine) {
    os << std::setw(10) << std::right << "x0_: " << std::setw(10) << std::right << affine.x0_ << std::setw(10)
       << std::right << " xi_: " << "{  ";
    for (const auto& [k, v] : affine.xi_) {
        os << k << ": " << v << ", ";
    }
    os << " }";

    return os;
}

/*!
 * @brief If the largest subscript of the noise term in the input affine expression is greater
 * than the static variable `i_`, we update `i_`.
 */
template<typename T>
Affine<T>::Affine(const T& x0, const std::unordered_map<int, T>& xi) :x0_(x0), xi_(xi) {
    int i = std::max_element(xi.begin(), xi.end(),
                             [](const auto& l, const auto& r) { return l.first < r.second; })->first + 1;
    i_ = i > i_ ? i : i_;
}

template<typename T>
Interval<T> Affine<T>::getInterval() const {
    T lo = x0_ - std::accumulate(xi_.begin(), xi_.end(), 0.,
                                 [](const T& prev, const auto& elem) { return prev + elem.second; });
    T hi = x0_ + std::accumulate(xi_.begin(), xi_.end(), 0.,
                                 [](const T& prev, const auto& elem) { return prev + elem.second; });
    return Interval{lo, hi};
}

template<typename T>
Affine<T> Affine<T>::operator+(const Affine<T>& rhs) const {
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

    return Affine{x0, xi};
}

template<typename T>
Affine<T> Affine<T>::operator*(const T& rhs) const {
    std::unordered_map<int, T> xi{xi_};
    std::for_each(xi.begin(), xi.end(), [rhs](auto& it) { it.second *= rhs; });
    return Affine{x0_ * rhs, xi};
}

template<typename U>
Affine<U> operator*(const U& lhs, const Affine<U>& rhs) {
    return rhs * lhs;
}

template<typename T>
T Affine<T>::getRad() const {
    using std::abs;
    return std::accumulate(xi_.begin(), xi_.end(), 0.,
                           [](const T& prev, const auto& elem) { return prev + abs(elem.second); });
}

template<typename T>
Affine<T> Affine<T>::operator*(const Affine& rhs) const {
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

    return Affine{x0, xi};
}

template<typename T>
Affine<T> Affine<T>::sigmoid() const {
    T lo = getLo();
    T hi = getHi();
    T f_lo = 1. / (1. + std::exp(-lo));
    T f_hi = 1. / (1. + std::exp(-hi));
    T lambda_opt = std::min((1 - f_lo) * f_lo, (1 - f_hi) * f_hi);
    T mu_1 = 0.5 * (f_hi + f_lo - lambda_opt * (hi + lo));
    T mu_2 = 0.5 * (f_hi - f_lo - lambda_opt * (hi - lo));

    Affine<T> res = *this * lambda_opt;
    res.x0_ += mu_1;
    res.xi_[i_++] = mu_2;

    return res;
}

template<typename T>
T Affine<T>::getLo() const {
    return x0_ - getRad();
}

template<typename T>
T Affine<T>::getHi() const {
    return x0_ + getRad();
}


#include "interval.h"

template<typename T>
Interval<T>::Interval(const T& lo, const T& hi) {
    if (lo > hi) {
        throw std::invalid_argument("lo > hi");
    }

    lo_ = std::move(lo);
    hi_ = std::move(hi);
}

template<typename T>
Interval<T> Interval<T>::operator+(const Interval& rhs) const {
    return Interval{lo_ + rhs.lo_, hi_ + rhs.hi_};
}

template<typename T>
Interval<T> Interval<T>::operator-(const Interval& rhs) const {
    return Interval{lo_ - rhs.hi_, hi_ - rhs.lo_};
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Interval<U>& interval) {
    os << std::setw(10) << std::right << "lo_: " << std::setw(10) << std::right << interval.lo_ << std::setw(10)
       << " hi_: " << std::setw(10)
       << std::right << interval.hi_;
    return os;
}

template<typename T>
Interval<T> Interval<T>::operator*(const Interval& rhs) const {
    std::vector<T> v{lo_ * rhs.lo_, lo_ * rhs.hi_, hi_ * rhs.lo_, hi_ * rhs.hi_};
    return Interval{*std::min_element(v.begin(), v.end()), *std::max_element(v.begin(), v.end())};
}

/*!
 * @brief Reference: https://github.com/JuliaIntervals/IntervalArithmetic.jl/blob/master/src/intervals/trigonometric.jl
 */
static int quad(double x) {
    double mod = x - 2 * M_PI * round(x / (2 * M_PI));
    if (mod < -M_PI / 2) {
        return 2;
    }
    if (mod < 0) {
        return 3;
    }
    if (mod <= M_PI / 2) {
        return 0;
    }
    return 1;
}

/*!
 * @brief Reference: https://github.com/JuliaIntervals/IntervalArithmetic.jl/blob/master/src/intervals/trigonometric.jl
 */
template<typename T>
Interval<T> sin(const Interval<T>& interval) {
    using std::sin;

    if (2 * M_PI < (double) (interval.hi_ - interval.lo_)) {
        return Interval{T{-1}, T{1}};
    }

    int lo_quad = quad((double) interval.lo_);
    int hi_quad = quad((double) interval.hi_);

    if (lo_quad == hi_quad) {
        if (M_PI < (double) (interval.hi_ - interval.lo_)) {
            return Interval{T{-1}, T{1}};
        }
        if (1 == lo_quad || 2 == lo_quad) {  // Negative slope.
            return Interval{T{sin(interval.hi_)}, T{sin(interval.lo_)}};
        }
        return Interval{T{sin(interval.lo_)}, T{sin(interval.hi_)}};
    }

    if (3 == lo_quad && 0 == hi_quad) {
        return Interval{T{sin(interval.lo_)}, T{sin(interval.hi_)}};
    }

    if (1 == lo_quad && 2 == hi_quad) {  // Negative slope.
        return Interval{T{sin(interval.hi_)}, T{sin(interval.lo_)}};
    }

    if ((0 == lo_quad || 3 == lo_quad) && (1 == hi_quad || 2 == hi_quad)) {
        if (sin(interval.lo_) < sin(interval.hi_)) {
            return Interval{T{sin(interval.lo_)}, T{1}};
        }
        return Interval{T{sin(interval.hi_)}, T{1}};
    }

    if ((1 == lo_quad || 2 == lo_quad) && (3 == hi_quad || 0 == hi_quad)) {
        if (sin(interval.lo_) < sin(interval.hi_)) {
            return Interval{T{-1}, T{sin(interval.hi_)}};
        }
        return Interval{T{-1}, T{sin(interval.lo_)}};
    }

    return Interval{T{-1}, T{1}};
}

/*!
 * @brief Reference: https://github.com/JuliaIntervals/IntervalArithmetic.jl/blob/master/src/intervals/trigonometric.jl
 */
template<typename T>
Interval<T> cos(const Interval<T>& interval) {
    using std::cos;

    if (2 * M_PI < (double) (interval.hi_ - interval.lo_)) {
        return Interval{T{-1}, T{1}};
    }

    int lo_quad = quad((double) interval.lo_);
    int hi_quad = quad((double) interval.hi_);

    if (lo_quad == hi_quad) {
        if (M_PI < (double) (interval.hi_ - interval.lo_)) {
            return Interval{T{-1}, T{1}};
        }
        if (2 == lo_quad || 3 == lo_quad) {  // Positive slope.
            return Interval{T{cos(interval.lo_)}, T{cos(interval.hi_)}};
        }
        return Interval{T{cos(interval.hi_)}, T{cos(interval.lo_)}};
    }

    if (2 == lo_quad && 3 == hi_quad) {
        return Interval{T{cos(interval.lo_)}, T{cos(interval.hi_)}};
    }

    if (0 == lo_quad && 1 == hi_quad) {  // Negative slope.
        return Interval{T{cos(interval.hi_)}, T{cos(interval.lo_)}};
    }

    if ((2 == lo_quad || 3 == lo_quad) && (0 == hi_quad || 1 == hi_quad)) {
        if (cos(interval.lo_) < cos(interval.hi_)) {
            return Interval{T{cos(interval.lo_)}, T{1}};
        }
        return Interval{T{cos(interval.hi_)}, T{1}};
    }

    if ((0 == lo_quad || 1 == lo_quad) && (2 == hi_quad || 3 == hi_quad)) {
        if (cos(interval.lo_) < cos(interval.hi_)) {
            return Interval{T{-1}, T{cos(interval.hi_)}};
        }
        return Interval{T{-1}, T{cos(interval.lo_)}};
    }

    return Interval{T{-1}, T{1}};
}

template<typename T>
Interval<T> exp(const Interval<T>& interval) {
    using std::exp;
    return Interval{exp(interval.lo_), exp(interval.hi_)};
}

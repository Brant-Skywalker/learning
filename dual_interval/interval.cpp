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
    os << std::setw(10) << std::right << "lo_: {" << std::setw(10) << std::right << interval.lo_ << std::setw(10)
       << "  }  hi_: {" << std::setw(10)
       << std::right << interval.hi_ << "  }";
    return os;
}

template<typename T>
Interval<T> Interval<T>::operator*(const Interval& rhs) const {
    std::vector<T> v{lo_ * rhs.lo_, lo_ * rhs.hi_, hi_ * rhs.lo_, hi_ * rhs.hi_};
    return Interval{*std::min_element(v.begin(), v.end()), *std::max_element(v.begin(), v.end())};
}

#ifndef AFFINE_INTERVAL__INTERVAL_H_
#define AFFINE_INTERVAL__INTERVAL_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <utility>

template<typename T>
class Interval {
public:
    T lo_{};
    T hi_{};

    Interval() = default;
    explicit Interval(const T& lo, const T& hi);
    virtual ~Interval() = default;

    Interval operator+(const Interval& rhs) const;
    Interval operator-(const Interval& rhs) const;
    Interval operator*(const Interval& rhs) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Interval<U>& interval);
};

template<typename T>
Interval<T> sin(const Interval<T>& interval);

template<typename T>
Interval<T> cos(const Interval<T>& interval);

template<typename T>
Interval<T> exp(const Interval<T>& interval);

#endif //AFFINE_INTERVAL__INTERVAL_H_

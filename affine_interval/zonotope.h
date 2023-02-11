#ifndef AFFINE_INTERVAL__ZONOTOPE_H_
#define AFFINE_INTERVAL__ZONOTOPE_H_

#include <unordered_map>
#include <numeric>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <utility>
#include "interval.h"

template<typename T>
class Zonotope {
    static inline int i_{1};
public:
    T x0_{};
    std::unordered_map<int, T> xi_{};

    // ctors and dtors.
    Zonotope() = default;
    explicit Zonotope(const Interval<T>& interval);
    explicit Zonotope(const T& x0, const std::unordered_map<int, T>& xi);
    virtual ~Zonotope() = default;

    Interval<T> getInterval() const;
    T getRad() const;
    Zonotope operator+(const Zonotope& rhs) const;
    Zonotope operator*(const Zonotope& rhs) const;

    // Scaling.
    Zonotope operator*(const T& rhs) const;
    template<typename U>
    friend Zonotope<U> operator*(const U& lhs, const Zonotope<U>& rhs);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Zonotope<U>& interval);
};

#endif //AFFINE_INTERVAL__ZONOTOPE_H_

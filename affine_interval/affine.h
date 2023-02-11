#ifndef AFFINE__AFFINE_H_
#define AFFINE__AFFINE_H_

#include <unordered_map>
#include <numeric>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <utility>
#include "interval.h"

template<typename T>
class Affine {
    static inline int i_{1};
public:
    T x0_{};
    std::unordered_map<int, T> xi_{};

    // ctors and dtors.
    Affine() = default;
    Affine(const Affine& affine) = default;
    Affine(Affine&& affine) noexcept = default;
    explicit Affine(const Interval<T>& interval);
    explicit Affine(const T& x0, const std::unordered_map<int, T>& xi);
    virtual ~Affine() = default;

    // Utilities.
    Interval<T> getInterval() const;
    T getRad() const;
    T getLo() const;
    T getHi() const;

    // Functions.
    Affine sigmoid() const;

    // Overloaded operators.
    Affine operator+(const Affine& rhs) const;
    Affine operator*(const Affine& rhs) const;

    // Scaling.
    Affine operator*(const T& rhs) const;
    template<typename U>
    friend Affine<U> operator*(const U& lhs, const Affine<U>& rhs);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Affine<U>& interval);
};

template<typename T>
Affine<T> sigmoid(const Affine<T>& affine) {
    return affine.sigmoid();
}

#endif //AFFINE__AFFINE_H_

#ifndef DUAL_INTERVAL__DUAL_H_
#define DUAL_INTERVAL__DUAL_H_

#include <ostream>
#include <iomanip>
#include <cmath>

template<typename T>
class Dual {
public:
    T real_{};
    T dual_{};

public:
    Dual() = default;
    explicit Dual(const T& real, const T& dual);
    virtual ~Dual() = default;

    Dual operator+(const Dual& rhs) const;
    Dual operator-(const Dual& rhs) const;
    Dual operator*(const Dual& rhs) const;

    bool operator<(const Dual& rhs) const;
    bool operator>(const Dual& rhs) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Dual<U>& dual);
};

template<typename T>
Dual<T> sin(const Dual<T>& dual);

template<typename T>
Dual<T> cos(const Dual<T>& dual);

template<typename T>
Dual<T> exp(const Dual<T>& dual);

#endif //DUAL_INTERVAL__DUAL_H_

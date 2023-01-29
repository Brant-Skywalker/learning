#ifndef DUAL_INTERVAL__DUAL_H_
#define DUAL_INTERVAL__DUAL_H_

#include <ostream>
#include <iomanip>
#include <cmath>

class Dual {
public:
    double real_{};
    double dual_{};

public:
    Dual() = default;
    explicit Dual(double real);
    explicit Dual(double real, double dual);
    virtual ~Dual() = default;

    Dual operator+(const Dual& rhs) const;
    Dual operator-(const Dual& rhs) const;
    Dual operator*(const Dual& rhs) const;

    bool operator<(const Dual& rhs) const;
    bool operator>(const Dual& rhs) const;

    explicit operator double() const;

    friend std::ostream& operator<<(std::ostream& os, const Dual& dual);
};

Dual sin(const Dual& dual);
Dual cos(const Dual& dual);
Dual exp(const Dual& dual);

#endif //DUAL_INTERVAL__DUAL_H_

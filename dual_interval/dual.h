#ifndef DUAL_INTERVAL__DUAL_H_
#define DUAL_INTERVAL__DUAL_H_

#include <ostream>
#include <iomanip>
#include <cmath>

class Dual {
public:
    double _real{};
    double _dual{};

public:
    Dual() = delete;
    explicit Dual(double real, double dual);
    virtual ~Dual() = default;

    Dual operator+(const Dual& rhs) const;
    Dual operator-(const Dual& rhs) const;
    Dual operator*(const Dual& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const Dual& dual);
};

Dual sin(const Dual& dual);
Dual exp(const Dual& dual);

#endif //DUAL_INTERVAL__DUAL_H_

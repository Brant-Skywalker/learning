#include <iostream>
#include "interval.h"
#include "interval.cpp"
#include "zonotope.h"
#include "zonotope.cpp"

int main() {
    Interval<double> i1{-2.3, 4.8};
    Interval<double> i2{-4.4, 9.6};

    std::cout << std::endl;
    std::cout << "Interval<double> i1 & i2" << std::endl;
    std::cout << i1 << std::endl;
    std::cout << i2 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<double> +" << std::endl;
    std::cout << i1 + i2 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<double> -" << std::endl;
    std::cout << i1 - i2 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<double> *" << std::endl;
    std::cout << i1 * i2 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<double> sin" << std::endl;
    std::cout << sin(i1) << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<double> exp" << std::endl;
    std::cout << exp(i1) << std::endl;

    Zonotope<double> z1{i1};

    std::cout << std::endl;
    std::cout << "Zonotope<double> z1 <-- i1 (Interval<double>)" << std::endl;
    std::cout << z1 << std::endl;

    Zonotope<double> z2{z1};

    std::cout << std::endl;
    std::cout << "Zonotope<double> z2 <-- z1 (Zonotope<double>)" << std::endl;
    std::cout << z2 << std::endl;

    // 1 + 2 * eps1 + 30 * eps2 --> [-31, 33]
    Zonotope<double> z3{1., {{1, 2.}, {2, 30.}}};

    std::cout << std::endl;
    std::cout << "Interval<double> z3" << std::endl;
    std::cout << z3 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<double> <-- z3 (Zonotope<double>)" << std::endl;
    std::cout << z3.getInterval() << std::endl;

    std::cout << std::endl;
    std::cout << "Zonotope<double> z1 + z3" << std::endl;
    std::cout << z1 + z3 << std::endl;

    Zonotope<double> z4{1., {{1, -5.55}, {2, -10.}}};

    std::cout << std::endl;
    std::cout << "Zonotope<double> z4" << std::endl;
    std::cout << z4 << std::endl;

    std::cout << std::endl;
    std::cout << "Zonotope<double> z1 + z3 + z4" << std::endl;
    std::cout << z1 + z3 + z4 << std::endl;

    return 0;
}

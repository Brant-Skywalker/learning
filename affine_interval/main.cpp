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

    return 0;
}

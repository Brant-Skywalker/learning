#include <iostream>
#include "dual.h"
#include "dual.cpp"
#include "interval.h"
#include "interval.cpp"

int main() {
    using std::sin;
    using std::cos;
    using std::exp;
    Dual<double> d1{3.7, 5.7};
    Dual<double> d2{-2.3, 4.8};

    std::cout << "Dual<double> d1 & d2" << std::endl;
    std::cout << d1 << std::endl;
    std::cout << d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<double> +" << std::endl;
    std::cout << d1 + d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<double> -" << std::endl;
    std::cout << d1 - d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<double> *" << std::endl;
    std::cout << d1 * d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<double> sin" << std::endl;
    std::cout << sin(d1) << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<double> cos" << std::endl;
    std::cout << cos(d1) << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<double> exp" << std::endl;
    std::cout << exp(d2) << std::endl;

    Interval<double> i1{-2.3, 4.8};
    Interval<double> i2{-4.4, 9.6};
//    Interval<double> ie1{2.3, -4.8};

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

    Dual<Interval<double>> di1{Interval{-2.3, 3.8}, Interval{4.8, 11.2}};
    Dual<Interval<double>> di2{Interval{-4.9, 8.6}, Interval{-4.8, -1.2}};

    std::cout << std::endl;
    std::cout << "Dual<Interval<double>> di1 & di2" << std::endl;
    std::cout << di1 << std::endl;
    std::cout << di2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<Interval<double>> +" << std::endl;
    std::cout << di1 + di2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<Interval<double>> -" << std::endl;
    std::cout << di1 - di2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<Interval<double>> *" << std::endl;
    std::cout << di1 * di2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<Interval<double>> sin" << std::endl;
    std::cout << sin(di1) << std::endl;
    std::cout << sin(di2) << std::endl;

    std::cout << std::endl;
    std::cout << "Dual<Interval<double>> exp" << std::endl;
    std::cout << exp(di1) << std::endl;
    return 0;
}

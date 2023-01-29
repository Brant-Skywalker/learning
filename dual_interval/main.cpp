#include <iostream>
#include "dual.h"
#include "interval.h"
#include "interval.cpp"

int main() {
    using std::sin;
    using std::cos;
    using std::exp;
    Dual d1{3.7, 5.7};
    Dual d2{-2.3, 4.8};

    std::cout << "Dual d1 & d2" << std::endl;
    std::cout << d1 << std::endl;
    std::cout << d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual +" << std::endl;
    std::cout << d1 + d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual -" << std::endl;
    std::cout << d1 - d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual *" << std::endl;
    std::cout << d1 * d2 << std::endl;

    std::cout << std::endl;
    std::cout << "Dual sin" << std::endl;
    std::cout << sin(d1) << std::endl;

    std::cout << std::endl;
    std::cout << "Dual cos" << std::endl;
    std::cout << cos(d1) << std::endl;

    std::cout << std::endl;
    std::cout << "Dual exp" << std::endl;
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

    Interval<Dual> i3{Dual{-2.3, -3.8}, Dual{4.8, 11.2}};
    Interval<Dual> i4{Dual{-4.9, 8.6}, Dual{-4.8, -1.2}};
//    Interval<Dual> ie2{Dual{4.9, 8.6}, Dual{-6.8, -1.2}};

    std::cout << std::endl;
    std::cout << "Interval<Dual> i3 & i4" << std::endl;
    std::cout << i3 << std::endl;
    std::cout << i4 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<Dual> +" << std::endl;
    std::cout << i3 + i4 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<Dual> -" << std::endl;
    std::cout << i3 - i4 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<Dual> *" << std::endl;
    std::cout << i3 * i4 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<Dual> sin" << std::endl;
    std::cout << sin(i3) << std::endl;
    std::cout << sin(i4) << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<Dual> exp" << std::endl;
    std::cout << exp(i3) << std::endl;
    return 0;
}

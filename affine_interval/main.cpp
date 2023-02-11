#include <iostream>
#include "interval.h"
#include "interval.cpp"
#include "affine.h"
#include "affine.cpp"

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

    Affine<double> z1{i1};

    std::cout << std::endl;
    std::cout << "Affine<double> z1 <-- i1 (Interval<double>)" << std::endl;
    std::cout << z1 << std::endl;

    Affine<double> z2{z1};

    std::cout << std::endl;
    std::cout << "Affine<double> z2 <-- z1 (Affine<double>)" << std::endl;
    std::cout << z2 << std::endl;

    // 1 + 2 * eps1 + 30 * eps2 --> [-31, 33]
    Affine<double> z3{1., {{1, 2.}, {2, 30.}}};

    std::cout << std::endl;
    std::cout << "Interval<double> z3" << std::endl;
    std::cout << z3 << std::endl;

    std::cout << std::endl;
    std::cout << "Interval<double> <-- z3 (Affine<double>)" << std::endl;
    std::cout << z3.getInterval() << std::endl;

    std::cout << std::endl;
    std::cout << "Affine<double> z1 + z3" << std::endl;
    std::cout << z1 + z3 << std::endl;

    Affine<double> z4{1., {{1, -5.55}, {2, -10.}}};

    std::cout << std::endl;
    std::cout << "Affine<double> z4" << std::endl;
    std::cout << z4 << std::endl;

    std::cout << std::endl;
    std::cout << "Affine<double> z1 + z3 + z4" << std::endl;
    std::cout << z1 + z3 + z4 << std::endl;

    std::cout << std::endl;
    std::cout << "Affine<double> z4 * 3." << std::endl;
    std::cout << z4 * 3. << std::endl;

    std::cout << std::endl;
    std::cout << "Affine<double> 3. * z4" << std::endl;
    std::cout << 4. * z4 << std::endl;

    std::cout << std::endl;
    std::cout << "Affine<double> z4.getRad() ==> " << z4.getRad() << std::endl;

    Affine<double> z5{1., {{1, 2.}, {2, 3.}}};

    std::cout << std::endl;
    std::cout << "Affine<double> z5 * z5" << std::endl;
    std::cout << z5 * z5 << std::endl;

    Affine<double> z6{Interval<double>{1, 5}};

    std::cout << std::endl;
    std::cout << "Affine<double> z6" << std::endl;
    std::cout << z6 << std::endl;  // Subscript should be 4.

    std::cout << std::endl;
    std::cout << "Affine<double> sigmoid(z6)" << std::endl;
    std::cout << sigmoid(z6) << std::endl;

    return 0;
}

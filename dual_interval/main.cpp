#include <iostream>
#include "dual.h"

int main() {
    using std::sin;
    using std::cos;
    using std::exp;
    Dual d1{3.7, 5.7};
    Dual d2{2.3, 5.8};

    std::cout << d1 + d2 << std::endl;
    std::cout << d1 - d2 << std::endl;
    std::cout << d1 * d2 << std::endl;
    std::cout << sin(d1) << std::endl;
    std::cout << cos(d1) << std::endl;
    std::cout << exp(d1) << std::endl;

    return 0;
}

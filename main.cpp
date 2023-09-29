#include <iostream>
#include "LongArithmetic.h"

int main()
{
    std::string k("123611");
    std::string r("25");

    LongNum k1(k);
    LongNum r1(r);

    std::cout << k1 + r1 << std::endl;
    std::cout << k1 - r1 << std::endl;
    std::cout << k1 * r1 << std::endl;
    std::cout << k1 / r1 << std::endl;
    std::cout << pow(k1, r1) << std::endl;
    return 0;
}
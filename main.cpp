#include <iostream>
#include "LongArithmetic.h"

int main()
{
    long long int a = 911111111111188881;
    long long int b = 919999999998888188;
    // std::cout << a + b << std::endl;

    std::string k("73244432432");
    std::string r("1");

    LongNum k1(k);
    LongNum r1(r);
    std::cout << k1 / r1 << std::endl;
    std::cout << k1 - r1 << std::endl;
    std::cout << k1 * r1 << std::endl;

    return 0;
}
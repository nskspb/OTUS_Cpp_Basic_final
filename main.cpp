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

    std::vector<int> a4{4, 2, 1, 3, 5, 4, 5, 4, 3};
    bool sign = true;
    LongNum r5(a4, sign);
    std::cout << r5 << std::endl;

    int y = 421354543;
    LongNum y5(y);

    if (y5 == r5)
    {
        std::cout << "@@@@@@@@";
    }

    return 0;
}
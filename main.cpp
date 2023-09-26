#include <iostream>
#include "LongArithmetic.h"

int main()
{
    long long int a = 911111111111188881;
    long long int b = 919999999998888188;
    // std::cout << a + b << std::endl;

    std::string k("68456842333333333333333333333333333333333334353453454354353454353453453454354354353423432432432434533333312");
    std::string r("134354353245333333333333333333333333333333333333333333333343543534333332432432432432432432432432432432423433333333333");

    LongNum k1(k);
    LongNum r1(r);

    LongNum *j1 = new LongNum(k);
    LongNum *g1 = new LongNum(r);

    std::cout << k1 + r1 << std::endl;
    std::cout << k1 - r1 << std::endl;
    std::cout << k1 * r1 << std::endl;
    LongNum h1 = j1->mult(r1, k1);
    std::cout << h1 << std::endl;
    std::cout << k1 / r1 << std::endl;

    return 0;
}
#include <iostream>
#include <string>
#include "../LongArithmetic.h"

#include <gtest/gtest.h>

class Test
{
private:
    static int totalTestNum;  // Total number of tests
    static int failedTestNum; // Number of failed tests
public:
    template <typename T1, typename T2>
    static bool verify(std::string testName, T1 recieved, T2 expected); // Assert function
    static void runAllTests();                                          // Run all tests
    static void printTestReport();                                      // Print out tests report
    static void test_sum();                                             // Test for +, +=
    static void test_sub();                                             // Test for -, -=
    static void test_mul();                                             // Test for *, *=
    static void test_div();                                             // Test for /, /=
    static void test_constructor();                                     // Test for constructor
    static void test_pow();                                             // Test for pow(x;y)
};

int Test::totalTestNum = 0;  // Total number of tests
int Test::failedTestNum = 0; // Number of failed tests

// Something like a custom assert function
// Verifies if recieved value matches expected value
template <typename T1, typename T2>
bool Test::verify(std::string testName, T1 recieved, T2 expected)
{
    totalTestNum++;
    if (recieved == expected)
    {
        return true;
    }
    else
    {
        failedTestNum++;
        std::cout << "FAILED TEST: " << testName << "\n";
        return false;
    }
}

void Test::runAllTests()
{
    std::cout << "\nRUNNING UNIT TESTS\n\n";
    test_sum();
    test_sub();
    test_mul();
    test_div();
    test_constructor();
    test_pow();
}

// Print out test report
void Test::printTestReport()
{
    std::cout << "\nTEST REPORT\n";
    std::cout << "Total tests:  " << totalTestNum << "\n";
    std::cout << "Failed tests: " << failedTestNum << "\n";
    if ((failedTestNum == 0) and (totalTestNum != 0))
    {
        std::cout << "\nALL TESTS PASSED CORRECTLY\n";
    }
    else if (totalTestNum != 0)
    {
        std::cout << "\nSOME TESTS FAILED TO PASS\n";
    }
    else
    {
        std::cout << "\nNO TESTS EXECUTED\n";
    }
}

void Test::test_sum()
{
    std::string a1("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678890");
    std::string b1("987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210983210");
    std::string result1("123456789012346666555555666655555566665555556666555555666655555566665555556666555555666655555566665555556662100");

    std::string a2("0");
    std::string b2("0");
    std::string result2("0");

    std::string a3("-123456");
    std::string b3("123456");
    std::string result3("0");

    std::string a4("15");
    std::string b4("15");
    std::string result4("30");

    std::string a5("99999999999999");
    std::string b5("1");
    std::string result5("100000000000000");

    std::string a6("-99999999999999");
    std::string b6("-1");
    std::string result6("-100000000000000");

    std::string a7("999");
    std::string b7("999");
    std::string result7("1998");

    verify("sum #1", LongNum(a1) + LongNum(b1), LongNum(result1));
    verify("sum #2", LongNum(a2) + LongNum(b2), LongNum(result2));
    verify("sum #3", LongNum(a3) + LongNum(b3), LongNum(result3));
    verify("sum #4", LongNum(a4) += LongNum(b4), LongNum(result4));
    verify("sum #5", LongNum(a5) + LongNum(b5), LongNum(result5));
    verify("sum #6", LongNum(a6) + LongNum(b6), LongNum(result6));
    verify("sum #7", LongNum(a7) + LongNum(b7), LongNum(result7));
}

void Test::test_sub()
{
    std::string a1("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678890");
    std::string b1("987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210983210");
    std::string result1("123456789012344691246913469124691346912469134691246913469124691346912469134691246913469124691346912469134695680");

    std::string a2("0");
    std::string b2("0");
    std::string result2("0");

    std::string a3("123456");
    std::string b3("123456");
    std::string result3("0");

    std::string a4("45");
    std::string b4("15");
    std::string result4("30");

    std::string a5("100000000000001");
    std::string b5("1");
    std::string result5("100000000000000");

    std::string a6("-99999999999999");
    std::string b6("1");
    std::string result6("-100000000000000");

    std::string a7("100000000000000");
    std::string b7("1");
    std::string result7("99999999999999");

    std::string a8("0");
    std::string b8("1");
    std::string result8("-1");

    verify("sub #1", LongNum(a1) - LongNum(b1), LongNum(result1));
    verify("sub #2", LongNum(a2) - LongNum(b2), LongNum(result2));
    verify("sub #3", LongNum(a3) - LongNum(b3), LongNum(result3));
    verify("sub #4", LongNum(a4) -= LongNum(b4), LongNum(result4));
    verify("sub #5", LongNum(a5) - LongNum(b5), LongNum(result5));
    verify("sub #6", LongNum(a6) - LongNum(b6), LongNum(result6));
    verify("sub #7", LongNum(a7) - LongNum(b7), LongNum(result7));
    verify("sub #8", LongNum(a8) - LongNum(b8), LongNum(result8));
}

void Test::test_mul()
{
    std::string a1("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678890");
    std::string b1("987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210983210");
    std::string result1("121932631137021795226185032733866788594511507391563633592367611644557885992987901082152001355951839648285183953732648874124979566287669424516284089240380123602913183828178835529606635267639538698231841436900");

    std::string a2("0");
    std::string b2("0");
    std::string result2("0");

    std::string a3("123456");
    std::string b3("123456");
    std::string result3("15241383936");

    std::string a4("30");
    std::string b4("15");
    std::string result4("450");

    std::string a5("100000000000001");
    std::string b5("1");
    std::string result5("100000000000001");

    std::string a6("-99999999999999");
    std::string b6("1");
    std::string result6("-99999999999999");

    std::string a7("100000000000000");
    std::string b7("0");
    std::string result7("0");

    std::string a8("0");
    std::string b8("1");
    std::string result8("0");

    std::string a9("100000000000000");
    std::string b9("1234567891234567");
    std::string result9("123456789123456700000000000000");

    std::string a10("100000000000000123");
    std::string b10("1234567891234567");
    std::string result10("123456789123456851851850621851741");

    verify("mul #1", LongNum(a1) * LongNum(b1), LongNum(result1));
    verify("mul #2", LongNum(a2) * LongNum(b2), LongNum(result2));
    verify("mul #3", LongNum(a3) * LongNum(b3), LongNum(result3));
    verify("mul #4", LongNum(a4) *= LongNum(b4), LongNum(result4));
    verify("mul #5", LongNum(a5) * LongNum(b5), LongNum(result5));
    verify("mul #6", LongNum(a6) * LongNum(b6), LongNum(result6));
    verify("mul #7", LongNum(a7) * LongNum(b7), LongNum(result7));
    verify("mul #8", LongNum(a8) * LongNum(b8), LongNum(result8));
    verify("mul #9", LongNum(a9) * LongNum(b9), LongNum(result9));
    verify("mul #9", LongNum(a10) * LongNum(b10), LongNum(result10));
}

void Test::test_div()
{
    std::string a1("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678890");
    std::string b1("987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210983210");
    std::string result1("124999998860937");

    std::string a2("0");
    std::string b2("1");
    std::string result2("0");

    std::string a3("123456");
    std::string b3("123456");
    std::string result3("1");

    std::string a4("30");
    std::string b4("15");
    std::string result4("2");

    std::string a5("100000000000001");
    std::string b5("1");
    std::string result5("100000000000001");

    std::string a6("-99999999999999");
    std::string b6("1");
    std::string result6("-99999999999999");

    std::string a7("100000000000000");
    std::string b7("10000000000000");
    std::string result7("10");

    std::string a8("15645646545646545646");
    std::string b8("8484165151514354548489489478974");
    std::string result8("0");

    std::string a9("95645646545646545646");
    std::string b9("84841651515143545484");
    std::string result9("1");

    std::string a10("90000000000000000000000000009");
    std::string b10("9");
    std::string result10("10000000000000000000000000001");

    std::string a11("-90000000000000000000000000009");
    std::string b11("10");
    std::string result11("-9000000000000000000000000000");

    verify("div #1", LongNum(a1) / LongNum(b1), LongNum(result1));
    verify("div #2", LongNum(a2) / LongNum(b2), LongNum(result2));
    verify("div #3", LongNum(a3) / LongNum(b3), LongNum(result3));
    verify("div #4", LongNum(a4) /= LongNum(b4), LongNum(result4));
    verify("div #5", LongNum(a5) / LongNum(b5), LongNum(result5));
    verify("div #6", LongNum(a6) / LongNum(b6), LongNum(result6));
    verify("div #7", LongNum(a7) / LongNum(b7), LongNum(result7));
    verify("div #8", LongNum(a8) / LongNum(b8), LongNum(result8));
    verify("div #9", LongNum(a9) / LongNum(b9), LongNum(result9));
    verify("div #10", LongNum(a10) / LongNum(b10), LongNum(result10));
    verify("div #11", LongNum(a11) / LongNum(b11), LongNum(result11));
}

void Test ::test_constructor()
{

    std::string a1("90000009");
    int b1 = 90000009;

    std::string a2("-90000009");
    int b2 = -90000009;

    std::string a3("0");
    int b3 = 0;

    verify("constructor #1", LongNum(a1), LongNum(b1));
    verify("constructor #2", LongNum(a2), LongNum(b2));
    verify("constructor #3", LongNum(a3), LongNum(b3));
}

void Test ::test_pow()
{
    std::string a1("0");
    std::string b1("1");
    std::string result1("0");

    // verify("pow #1", pof(LongNum(a1), LongNum(b1)), LongNum(result1));
}

int main(int argc, char *argv[])
{

    Test::runAllTests();
    Test::printTestReport();

    return 0;
}
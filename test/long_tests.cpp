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
    static bool verify(std::string testName, T1 recieved, T2 expected); // Custom assert function
    static void test_sum();                                             // Test operators +, +=
    static void runAllTests();                                          // Run all tests
    static void printTestReport();                                      // Print out tests report
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

    verify("sum #1", LongNum(a1) + LongNum(b1), LongNum(result1));
    verify("sum #2", LongNum(a2) + LongNum(b2), LongNum(result2));
    verify("sum #3", LongNum(a3) + LongNum(b3), LongNum(result3));
    verify("sum #4", LongNum(a4) += LongNum(b4), LongNum(result4));
    verify("sum #5", LongNum(a5) += LongNum(b5), LongNum(result5));
}

int main(int argc, char *argv[])
{

    Test::runAllTests();
    Test::printTestReport();

    return 0;
}
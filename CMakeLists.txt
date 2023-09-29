cmake_minimum_required(VERSION 3.5)

project(LongArithmetic)


include_directories(test)

add_executable(long_arithmetic
main.cpp)

set_target_properties(long_arithmetic PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(run_tests
test/run_test.cpp
)

target_include_directories(run_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/headers")

set_target_properties(run_tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
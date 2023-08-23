
cmake_minimum_required(VERSION 3.10)

project(LongArithmetic)

add_executable(long_arithmetic
main.cpp)
set_target_properties(long_arithmetic PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


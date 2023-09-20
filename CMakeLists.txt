cmake_minimum_required(VERSION 3.5)

project(LongArithmetic)

find_package(GTest)

include_directories(test)

add_executable(long_arithmetic
main.cpp)

set_target_properties(long_arithmetic PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(run_tests
test/long_tests.cpp
)

target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(run_tests ${GTEST_BOTH_LIBRARIES})
target_include_directories(run_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/headers")

message(STATUS ${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_BOTH_LIBRARIES})


set_target_properties(run_tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
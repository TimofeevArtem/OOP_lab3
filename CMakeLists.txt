cmake_minimum_required(VERSION 3.16)
project(OOP_lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

enable_testing()

add_executable(main main.cpp complex.cpp complexSet.cpp)
add_executable(complex_tests gtests.cpp complex.cpp complexSet.cpp)
target_link_libraries(complex_tests PRIVATE GTest::gtest_main)
add_test(NAME complex_tests COMMAND complex_tests)
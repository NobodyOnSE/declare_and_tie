cmake_minimum_required (VERSION 2.6)

project(Declare_and_tie_tests)

include_directories(..)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(Boost COMPONENTS unit_test_framework)

add_executable(unit_tests test.cpp unit_tests.cpp)

target_link_libraries(unit_tests ${Boost_LIBRARIES})
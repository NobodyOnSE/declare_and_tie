cmake_minimum_required (VERSION 2.6)

project(Declare_and_tie_tests)

find_package(Boost COMPONENTS unit_test_framework)

add_executable(unit_tests test.cpp)

target_link_libraries(unit_tests ${Boost_LIBRARIES})
#include "test.hpp"

#include <declare_and_tie.hpp>

BOOST_AUTO_TEST_CASE(Test_reference_to_tuple_elements) {
	auto tuple = std::make_tuple(1, 0.5, std::string("hello world"));
	DECLARE_AND_TIE((integer, real, string), tuple);
}


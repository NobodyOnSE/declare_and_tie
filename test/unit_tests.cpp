#include "test.hpp"

#include <declare_and_tie.hpp>

BOOST_AUTO_TEST_CASE(Test_reference_to_tuple_elements) {
	auto tuple = std::make_tuple(1, 0.5, std::string("hello world"));
	DECLARE_AND_TIE((a, b, c), tuple);
	BOOST_REQUIRE(std::is_reference<decltype(a)>::value);
	BOOST_REQUIRE_EQUAL(&a, &std::get<0>(tuple));
	BOOST_REQUIRE(std::is_reference<decltype(b)>::value);
	BOOST_REQUIRE_EQUAL(&b, &std::get<1>(tuple));
	BOOST_REQUIRE(std::is_reference<decltype(c)>::value);
	BOOST_REQUIRE_EQUAL(&c, &std::get<2>(tuple));
}

template <class T>
using isConstRef = std::is_const<typename std::remove_reference<T>::type>;

BOOST_AUTO_TEST_CASE(Test_retain_tuple_constness) {
	auto const tuple = std::make_tuple(1, 0.5, std::string("hello world"));

	BOOST_REQUIRE(std::is_const<decltype(tuple)>::value);

	DECLARE_AND_TIE((a, b, c), tuple);

	BOOST_REQUIRE(isConstRef<decltype(a)>::value);
	BOOST_REQUIRE(isConstRef<decltype(b)>::value);
	BOOST_REQUIRE(isConstRef<decltype(c)>::value);
}

BOOST_AUTO_TEST_CASE(Test_retain_tuple_element_constness) {
	std::tuple<const int, double, const char*> tuple(1, 0.5, "hello world");

	BOOST_REQUIRE(!std::is_const<decltype(tuple)>::value);

	DECLARE_AND_TIE((a, b, c), tuple);

	BOOST_REQUIRE(isConstRef<decltype(a)>::value);
	BOOST_REQUIRE(!isConstRef<decltype(b)>::value);
	// the pointer is not const!
	BOOST_REQUIRE(!isConstRef<decltype(c)>::value);
}

BOOST_AUTO_TEST_CASE(Test_multiple_ties) {
	const auto tuple = std::make_tuple(1, 0.5, std::string("hello world"));
	DECLARE_AND_TIE((a, b, c), tuple);
	DECLARE_AND_TIE((d, e, f), tuple);
}

/*
BOOST_AUTO_TEST_CASE(Test_error_on_rvalue_cpp_tuple) {
	DECLARE_AND_TIE((integer, real, string),
			std::make_tuple(1, 0.5, std::string("hello world")));
}
*/

/*
BOOST_AUTO_TEST_CASE(Test_error_on_non_tuple_unpack_list) {
	auto tuple = std::make_tuple(1, 0.5, std::string("hello world"));
    DECLARE_AND_TIE(one_parameter, tuple);
}
*/

/*
BOOST_AUTO_TEST_CASE(Test_error_on_missing_trailing_semicolon) {
	auto tuple = std::make_tuple(1, 0.5, std::string("hello world"));
	// error about missing semicolon
	DECLARE_AND_TIE((a, b, c), tuple)
}
*/

/*
BOOST_AUTO_TEST_CASE(Test_error_on_too_many_unpack_elements) {
	std::tuple<const int, double, std::string> tuple(1, 0.5, "hello world");
	DECLARE_AND_TIE((a, b, c, d), tuple);
}
*/

/*
BOOST_AUTO_TEST_CASE(Test_error_on_too_few_unpack_elements) {
	std::tuple<const int, double, std::string> tuple(1, 0.5, "hello world");
	DECLARE_AND_TIE((a, b), tuple);
}
*/

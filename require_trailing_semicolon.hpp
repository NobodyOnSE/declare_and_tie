#ifndef REQUIRE_TRAILING_SEMICOLON_HPP_
#define REQUIRE_TRAILING_SEMICOLON_HPP_

#include <boost/preprocessor/cat.hpp>

#define REQUIRE_TRAILING_SEMICOLON()                                           \
    struct BOOST_PP_CAT(trailing_semicolon_required_on_line_, __LINE__) {}

#endif /* REQUIRE_TRAILING_SEMICOLON_HPP_ */

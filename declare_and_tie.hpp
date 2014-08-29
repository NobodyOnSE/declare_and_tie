#ifndef _guard_DECLARE_AND_TIE_HPP_
#define _guard_DECLARE_AND_TIE_HPP_

#if not(BOOST_PP_VARIADICS)
#error "Boost preprocessor variadics support needed for DECLARE_AND_TIE!"
#endif

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include "is_boost_pp_tuple.hpp"
#include "require_trailing_semicolon.hpp"

/**
 * @brief Declare references to tuple elements with the given names
 * @param UNPACKED_ELEMENTS a boost preprocessor tuple of names for references
 * @param TUPLE to unpack
 *
 * Example usages:
 *
 * std::tuple<int, float, string> cppTuple;
 * DECLARE_AND_TIE((a, b, c), cppTuple);
 *
 * std::tuple<int, float, string> cppTuple;
 * //ignoring the float element
 * DECLARE_AND_TIE((a, _, c), cppTuple);
 */
#define DECLARE_AND_TIE(UNPACKED_ELEMENTS, TUPLE)                              \
    static_assert(BOOST_PP_IS_TUPLE(UNPACKED_ELEMENTS),                        \
                  "First parameter must be a tuple!");                         \
    static_assert(!COMPARE_SIZE(UNPACKED_ELEMENTS, >, TUPLE),                  \
                  "Too many unpacked elements for tuple");                     \
    static_assert(!COMPARE_SIZE(UNPACKED_ELEMENTS, <, TUPLE),                  \
                  "Too few unpacked elements for tuple");                      \
    _impl_DECLARE_AND_TIE_VARIABLES(UNPACKED_ELEMENTS, TUPLE)
    REQUIRE_TRAILING_SEMICOLON()

#define COMPARE_SIZE(UNPACKED, REL, TUPLE)                                     \
	(BOOST_PP_TUPLE_SIZE(UNPACKED) REL std::tuple_size<decltype(TUPLE)>::value)

#define _impl_DECLARE_AND_TIE_ONE_VARIABLE(r, TUPLE, INDEX, VARNAME)           \
	BOOST_PP_IF(_impl_TOKEN_IS_UNDERSCORE(VARNAME),                            \
				_impl_DECLARE_AND_TIE_UNDERSCORE,                              \
				_impl_DECLARE_AND_TIE_VARIABLE)(r, TUPLE, INDEX, VARNAME)

#define _impl_TOKEN_IS_UNDERSCORE_TEST_(x) x

#define _impl_TOKEN_IS_UNDERSCORE(a)                                           \
	BOOST_MPL_PP_IS_SEQ(                                                       \
		BOOST_PP_CAT(_impl_TOKEN_IS_UNDERSCORE_TEST, a)((unused)))

#define _impl_DECLARE_AND_TIE_UNDERSCORE(r, TUPLE, INDEX, VARNAME)

#define _impl_DECLARE_AND_TIE_VARIABLE(r, TUPLE, ELEMENT_INDEX, VARIABLE_NAME) \
    auto& VARIABLE_NAME = std::get<ELEMENT_INDEX>(TUPLE);

#define _impl_DECLARE_AND_TIE_VARIABLES(UNPACKED_ELEMENTS, TUPLE)              \
	BOOST_PP_SEQ_FOR_EACH_I(_impl_DECLARE_AND_TIE_ONE_VARIABLE, TUPLE,         \
							BOOST_PP_TUPLE_TO_SEQ(UNPACKED_ELEMENTS))

#endif /* _guard_DECLARE_AND_TIE_HPP_ */

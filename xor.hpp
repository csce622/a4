/**
 *
 * @file xor.hpp
 *
 * @brief logical operation exclusive or
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 18, 2010
 */

#ifndef XOR_HPP
#define XOR_HPP

#include <boost/mpl/logical.hpp>
#include <boost/mpl/assert.hpp>

using namespace boost;

template <typename F1, typename F2>
struct xor_ : mpl::and_<
  mpl::or_<F1, F2>,
  mpl::not_< mpl::and_<F1, F2> >
> {};

BOOST_MPL_ASSERT_NOT(( xor_< mpl::true_, mpl::true_ > ));
BOOST_MPL_ASSERT(( xor_< mpl::true_, mpl::false_ > ));
BOOST_MPL_ASSERT(( xor_< mpl::false_, mpl::true_ > ));
BOOST_MPL_ASSERT_NOT(( xor_< mpl::false_, mpl::false_ > ));

#endif // XOR_HPP

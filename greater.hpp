/**
 *
 * @title greater.hpp
 *
 * @brief metafunction greater takes two element types and returns true if the
 * first element is greater than or equal to the second (with respect to the
 * partial ordering defined in Assignment 4).
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 15, 2010
 */

#ifndef GREATER_HPP
#define GREATER_HPP

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>

#include "upper.hpp"

using namespace boost;

template <typename T1, typename T2>
struct greater 
{
  typedef typename mpl::if_< 
    typename mpl::equal< 
      typename upper<T1, T2>::type,
       T1 
    >::type,
    mpl::true_,
    mpl::false_
   >::type type;
  BOOST_MPL_ASSERT_MSG( (type::value), PARTIAL_ORDER_VIOLATED, (T1, T2) );
};

#endif // GREATER_HPP

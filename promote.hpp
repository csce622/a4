/**
 *
 * @file promote.hpp
 *
 * @brief metafunction promote takes two sequences and returns a new sequence
 * of the same length, where each element is the least upper bound (according
 * to the partial order defined in Assignment 4) 
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 18, 2010
 */

#ifndef PROMOTE_HPP
#define PROMOTE_HPP

#include <complex>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/clear.hpp>

#include "upper.hpp"

using namespace boost;

template <
  typename Sequence1, 
  typename Sequence2, 
  typename Iterator1, 
  typename Iterator2, 
  typename Output, 
  typename Position,
  bool Condition = is_same<
    typename mpl::end<Sequence1>::type, 
    Iterator1
  >::value
>
struct __promote {
  typedef typename __promote<
    Sequence1, 
    Sequence2, 
    typename mpl::next<Iterator1>::type, 
    typename mpl::next<Iterator2>::type, 
    typename mpl::insert<
      Output, 
      Position,
      typename upper<
        typename mpl::deref<Iterator1>::type,
        typename mpl::deref<Iterator2>::type
      >::type
    >::type,
    typename mpl::next<Position>::type
  >::type type;
};

template <
  typename Sequence1, 
  typename Sequence2, 
  typename Iterator1, 
  typename Iterator2, 
  typename Output,
  typename Position>
struct __promote<Sequence1, Sequence2, Iterator1, Iterator2, Output, Position, true> {
  typedef Output type;
};

template <typename S1, typename S2>
struct promote {
  BOOST_MPL_ASSERT_MSG( (is_same< typename mpl::size<S1>::type, typename mpl::size<S2>::type >::value), SEQUENCES_MUST_HAVE_SAME_SIZE, () );
  typedef typename mpl::clear<S1>::type Output;
  typedef typename __promote<
    S1, 
    S2, 
    typename mpl::begin<S1>::type, 
    typename mpl::begin<S2>::type, 
    Output,
    typename mpl::begin<Output>
  >::type type;
};

#endif // PROMOTE_HPP

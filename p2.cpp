/**
 *
 * CSCE-622: Generic Programming -- Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 12, 2010
 */

#include <iostream>
#include <cassert>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/transform.hpp>

using namespace boost;
using mpl::placeholders::_;
using mpl::placeholders::_1;
using mpl::placeholders::_2;

// DUMMY VERSION WORKS FINE //////////////
template <typename T1, typename T2>
struct promote_dummy {
  typedef T2 type;
};
/////////////////////////////////////////

typedef mpl::lambda<_2>::type myfunc;

template <typename T1, typename T2>
struct promote : mpl::apply<myfunc, T1, T2> {};

BOOST_MPL_ASSERT(( is_same<promote<double, char>::type, char > ));





int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p2 # \n";
  std::cout << "######  \n";

  // DUMMY VERSION WORKS FINE //////////////
  typedef mpl::vector<char, double, int> s1;
  typedef mpl::vector<double, double, long> s2;
  BOOST_MPL_ASSERT_MSG( (mpl::equal<promote_dummy<s1,s2>::type, s2>::type::value), CASSE_COUILLE, () );
  // The following line will fail at run time.
  assert(( mpl::equal<s1, s2>::type::value ));
  /////////////////////////////////////////
  
  BOOST_MPL_ASSERT(( mpl::less<mpl::int_<2>, mpl::int_<10> > ));

  BOOST_MPL_ASSERT(( mpl::equal<myfunc::apply<s1, s2>, s1>::type::value ));

  //BOOST_MPL_ASSERT(( mpl::equal<promote<s1, s2>, s2>::type ));

  return 0;
}

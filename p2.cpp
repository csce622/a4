/**
 *
 * CSCE-622: Generic Programming -- Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 12, 2010
 */

#include <iostream>
#include <cassert>
#include <complex>
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
#include <boost/mpl/logical.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_complex.hpp>

using namespace boost;
using mpl::placeholders::_;
using mpl::placeholders::_1;
using mpl::placeholders::_2;


template <typename T1, typename T2> 
struct greater { 
  typedef typename mpl::if_c<  
    !(sizeof(T1) < sizeof(T2)), 
    mpl::true_, 
    mpl::false_ 
  >::type type; 
}; 


BOOST_MPL_ASSERT(( is_integral<char> ));
BOOST_MPL_ASSERT(( is_integral<int> ));
BOOST_MPL_ASSERT(( is_integral<long> ));
BOOST_MPL_ASSERT(( mpl::not_< is_integral<float> > ));
BOOST_MPL_ASSERT(( mpl::not_< is_integral<double> > ));
BOOST_MPL_ASSERT(( mpl::not_< is_complex<double> > ));
BOOST_MPL_ASSERT(( is_complex< std::complex<double> > ));

template <
  typename T1, 
  typename T2, 
  bool T1_is_integral = is_integral<T1>::value,
  bool T2_is_integral = is_integral<T2>::value
>
struct least_upper_bound {
  typedef typename mpl::if_c<
    (sizeof(T1)>sizeof(T2)),
    T1,
    T2
  >::type type;
};

template<typename F1, typename F2>
struct xor_ : mpl::and_<
  mpl::or_<F1, F2>,
  mpl::not_< mpl::and_<F1, F2> >
> {};

// not determined yet
template <typename T1, typename T2>
struct least_upper_bound<T1, T2, false, false> {
  typedef void type;
};

template <typename T1, typename T2>
struct least_upper_bound<T1, T2, true, false> {
  typedef T2 type;
};

template <typename T1, typename T2>
struct least_upper_bound<T1, T2, false, true> {
  typedef T1 type;
};

//BOOST_MPL_ASSERT(( is_same< least_upper_bound<double, double>::type, double > ));
//BOOST_MPL_ASSERT(( is_same< least_upper_bound<double, float>::type, double > ));
//BOOST_MPL_ASSERT(( is_same< least_upper_bound<float, double>::type, double > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<double, long>::type, double > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<long, double>::type, double > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<double, int>::type, double > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<int, double>::type, double > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<double, char>::type, double > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<char, double>::type, double > ));

//BOOST_MPL_ASSERT(( is_same< least_upper_bound<float, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<float, long>::type, float > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<long, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<int, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<float, int>::type, float > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<char, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<float, char>::type, float > ));

BOOST_MPL_ASSERT(( is_same< least_upper_bound<long, long>::type, long > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<long, int>::type, long > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<int, long>::type, long > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<long, char>::type, long > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<char, long>::type, long > ));

BOOST_MPL_ASSERT(( is_same< least_upper_bound<int, int>::type, int > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<int, char>::type, int > ));
BOOST_MPL_ASSERT(( is_same< least_upper_bound<char, int>::type, int > ));

BOOST_MPL_ASSERT(( is_same< least_upper_bound<char, char>::type, char > ));

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
  //assert(( mpl::equal<s1, s2>::type::value ));
  /////////////////////////////////////////
  
  BOOST_MPL_ASSERT(( mpl::less<mpl::int_<2>, mpl::int_<10> > ));

  BOOST_MPL_ASSERT(( mpl::equal<myfunc::apply<s1, s2>, s1>::type::value ));

  //BOOST_MPL_ASSERT(( mpl::equal<promote<s1, s2>, s2>::type ));

  std::cout << "char   " << sizeof(char  ) << "\n";
  std::cout << "int    " << sizeof(int   ) << "\n";
  std::cout << "long   " << sizeof(long  ) << "\n";
  std::cout << "float  " << sizeof(float ) << "\n";
  std::cout << "double " << sizeof(double) << "\n";
  std::cout << "complex<float>  " << sizeof(std::complex<float>) << "\n";
  std::cout << "complex<double> " << sizeof(std::complex<double>) << "\n";

  return 0;
}

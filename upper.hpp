/**
 *
 * @file upper.hpp
 *
 * @brief metafunction upper takes two types and returns the least upper bound
 * according to the partial order defined in Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 16, 2010
 */

#ifndef UPPER_HPP
#define UPPER_HPP

#include <complex>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_complex.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>

#include "xor.hpp"

using namespace boost;

template <
  typename T1, 
  typename T2, 
  bool T1_is_integral = is_integral<T1>::value,
  bool T2_is_integral = is_integral<T2>::value
>
struct upper {
  typedef typename mpl::if_c<
    (sizeof(T1)>sizeof(T2)),
    T1,
    T2
  >::type type;
};

// not very elegant but works fine :D
template <typename T1, typename T2>
struct tweak {
  typedef typename mpl::if_<
    is_complex<T1>,
    T1,
    T2
  >::type type;
};

template <>
struct tweak< std::complex<float>, double > {
  typedef std::complex<double> type;
};

template <>
struct tweak< double, std::complex<float> > {
  typedef std::complex<double> type;
};

template <typename T1, typename T2>
struct upper<T1, T2, false, false> {
  typedef typename mpl::if_<
    xor_<
      is_complex<T1>,
      is_complex<T2>
    >,
    typename tweak<
      T1, 
      T2
    >::type,
    typename mpl::if_c<
      (sizeof(T1)>sizeof(T2)),
      T1,
      T2
    >::type
  >::type type;
};

template <typename T1, typename T2>
struct upper<T1, T2, true, false> {
  typedef T2 type;
};

template <typename T1, typename T2>
struct upper<T1, T2, false, true> {
  typedef T1 type;
};

BOOST_MPL_ASSERT(( is_same< upper< std::complex<double>, std::complex<double> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<double>, std::complex<float> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<float>, std::complex<double> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<double>, double >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< double, std::complex<double> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<double>, float >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< float, std::complex<double> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<double>, long >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< long, std::complex<double> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<double>, int >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< int, std::complex<double> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<double>, char >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< char, std::complex<double> >::type, std::complex<double> > ));

BOOST_MPL_ASSERT(( is_same< upper< std::complex<float>, std::complex<float> >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<float>, double >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< double, std::complex<float> >::type, std::complex<double> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<float>, float >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< float, std::complex<float> >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<float>, long >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< long, std::complex<float> >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<float>, int >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< int, std::complex<float> >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< std::complex<float>, char >::type, std::complex<float> > ));
BOOST_MPL_ASSERT(( is_same< upper< char, std::complex<float> >::type, std::complex<float> > ));

BOOST_MPL_ASSERT(( is_same< upper<double, double>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<double, float>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<float, double>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<double, long>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<long, double>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<double, int>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<int, double>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<double, char>::type, double > ));
BOOST_MPL_ASSERT(( is_same< upper<char, double>::type, double > ));

BOOST_MPL_ASSERT(( is_same< upper<float, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< upper<float, long>::type, float > ));
BOOST_MPL_ASSERT(( is_same< upper<long, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< upper<int, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< upper<float, int>::type, float > ));
BOOST_MPL_ASSERT(( is_same< upper<char, float>::type, float > ));
BOOST_MPL_ASSERT(( is_same< upper<float, char>::type, float > ));

BOOST_MPL_ASSERT(( is_same< upper<long, long>::type, long > ));
BOOST_MPL_ASSERT(( is_same< upper<long, int>::type, long > ));
BOOST_MPL_ASSERT(( is_same< upper<int, long>::type, long > ));
BOOST_MPL_ASSERT(( is_same< upper<long, char>::type, long > ));
BOOST_MPL_ASSERT(( is_same< upper<char, long>::type, long > ));

BOOST_MPL_ASSERT(( is_same< upper<int, int>::type, int > ));
BOOST_MPL_ASSERT(( is_same< upper<int, char>::type, int > ));
BOOST_MPL_ASSERT(( is_same< upper<char, int>::type, int > ));

BOOST_MPL_ASSERT(( is_same< upper<char, char>::type, char > ));

#endif // UPPER_HPP

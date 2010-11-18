/**
 *
 * CSCE-622: Generic Programming -- Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 16, 2010
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
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/deque.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/clear.hpp>

using namespace boost;
using mpl::placeholders::_1;
using mpl::placeholders::_2;

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

template <typename F1, typename F2>
struct xor_ : mpl::and_<
  mpl::or_<F1, F2>,
  mpl::not_< mpl::and_<F1, F2> >
> {};

BOOST_MPL_ASSERT_NOT(( xor_< mpl::true_, mpl::true_ > ));
BOOST_MPL_ASSERT(( xor_< mpl::true_, mpl::false_ > ));
BOOST_MPL_ASSERT(( xor_< mpl::false_, mpl::true_ > ));
BOOST_MPL_ASSERT_NOT(( xor_< mpl::false_, mpl::false_ > ));

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



/// a la main //////////////////////////////
template <typename S1, typename S2>
struct foo {
  BOOST_MPL_ASSERT_MSG( (is_same< typename mpl::size<S1>::type, typename mpl::size<S2>::type >::value), 
    SEQUENCES_MUST_HAVE_SAME_SIZE, (S1, S2) );
  typedef typename mpl::begin<S1>::type iter_S1;
  typedef typename mpl::begin<S2>::type iter_S2;
  typedef typename upper<
    typename mpl::deref<iter_S1>::type,
    typename mpl::deref<iter_S2>::type
  >::type type1;
  typedef typename upper<
    typename mpl::deref< typename mpl::next<iter_S1>::type >::type,
    typename mpl::deref< typename mpl::next<iter_S2>::type >::type
  >::type type2;
};

BOOST_MPL_ASSERT(( is_same< foo< mpl::vector<double, int>, mpl::vector<long, float> >::type1, double > ));
BOOST_MPL_ASSERT(( is_same< foo< mpl::vector<double, int>, mpl::vector<long, float> >::type2, float > ));

/// boucle recopie une sequence ///////////////////
template <typename Sequence, typename Iterator, typename Copy, 
  bool Condition = is_same<typename mpl::end<Sequence>::type, Iterator>::value >
struct bar {
  typedef typename bar<
    Sequence, 
    typename mpl::next<Iterator>::type, 
    typename mpl::push_back<
      Copy, 
      typename mpl::deref<Iterator>::type
    >::type
  >::type type;
};

template <typename Sequence, typename Iterator, typename Copy>
struct bar<Sequence, Iterator, Copy, true> {
  typedef Copy type;
};

typedef mpl::vector<double, char, int> enfer;
typedef bar< enfer::type, mpl::begin<enfer::type>::type, mpl::vector<> >::type damnation;
//BOOST_MPL_ASSERT(( is_same< damnation, enfer > ));
BOOST_MPL_ASSERT(( mpl::equal< damnation, enfer > ));


/// eureka ///////////////////////////////
template <
  typename Sequence1, 
  typename Sequence2, 
  typename Iterator1, 
  typename Iterator2, 
  typename Output, 
  bool Condition = is_same<
    typename mpl::end<Sequence1>::type, 
    Iterator1
  >::value
>
struct eureka {
  typedef typename eureka<
    Sequence1, 
    Sequence2, 
    typename mpl::next<Iterator1>::type, 
    typename mpl::next<Iterator2>::type, 
    typename mpl::push_back<
      Output, 
      typename upper<
        typename mpl::deref<Iterator1>::type,
        typename mpl::deref<Iterator2>::type
      >::type
    >::type
  >::type type;
};

template <
  typename Sequence1, 
  typename Sequence2, 
  typename Iterator1, 
  typename Iterator2, 
  typename Output>
struct eureka<Sequence1, Sequence2, Iterator1, Iterator2, Output, true> {
  typedef Output type;
};

/// encapsulate eureka -> promote ///////////////////////////////
template <typename S1, typename S2>
struct promote {
  BOOST_MPL_ASSERT_MSG( (is_same< typename mpl::size<S1>::type, typename mpl::size<S2>::type >::value), SEQUENCES_MUST_HAVE_SAME_SIZE, () );
  typedef typename eureka<
    S1, 
    S2, 
    typename mpl::begin<S1>::type, 
    typename mpl::begin<S2>::type, 
    typename mpl::clear<S1>::type
  >::type type;
};





int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p2 # \n";
  std::cout << "######  \n";

  // checking example in the assignment
  typedef mpl::vector<char, double, int> s1;
  typedef mpl::vector<double, double, long> s2;
  BOOST_MPL_ASSERT(( mpl::equal< promote<s1, s2>::type, s2 > ));

  // another check
  BOOST_MPL_ASSERT(( mpl::equal<
    promote<
      mpl::deque<double, int, char, long, long, float>,
      mpl::deque<char, std::complex<float>, long, int, float, double>
    >::type, 
    mpl::deque<double, std::complex<float>, long, long, float, double> 
  > ));

  // The following line will fail at run time.
  //assert(( mpl::equal<s1, s2>::type::value ));
  

  std::cout << "char   " << sizeof(char  ) << "\n";
  std::cout << "int    " << sizeof(int   ) << "\n";
  std::cout << "long   " << sizeof(long  ) << "\n";
  std::cout << "float  " << sizeof(float ) << "\n";
  std::cout << "double " << sizeof(double) << "\n";
  std::cout << "complex<float>  " << sizeof(std::complex<float>) << "\n";
  std::cout << "complex<double> " << sizeof(std::complex<double>) << "\n";

  return 0;
}

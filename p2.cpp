/**
 *
 * @file p2.cpp
 *
 * @brief CSCE-622: Generic Programming -- Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 16, 2010
 */

#include <iostream>
#include <cassert>
#include <complex>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/deque.hpp>
#include <boost/mpl/list.hpp>

#include "promote.hpp"

using namespace boost;

int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p2 # \n";
  std::cout << "######  \n";

  // checking example in the assignment
  typedef mpl::vector<char, double, int> s1;
  typedef mpl::vector<double, double, long> s2;
  BOOST_MPL_ASSERT(( mpl::equal< promote<s1, s2>::type, s2 > ));

  // example with a deque
  BOOST_MPL_ASSERT(( mpl::equal<
    promote<
      mpl::deque<double, int, char, long, long, float>,
      mpl::deque<char, std::complex<float>, long, int, float, double>
    >::type, 
    mpl::deque<double, std::complex<float>, long, long, float, double> 
  > ));

  // example with a list
  BOOST_MPL_ASSERT(( mpl::equal<
    promote<
      mpl::list<complex<double>, int, char>,
      mpl::list<complex<float>, long, long>
    >::type, 
    mpl::list<std::complex<double>, long, long> 
  > ));

  std::cout << "char   " << sizeof(char  ) << "\n";
  std::cout << "int    " << sizeof(int   ) << "\n";
  std::cout << "long   " << sizeof(long  ) << "\n";
  std::cout << "float  " << sizeof(float ) << "\n";
  std::cout << "double " << sizeof(double) << "\n";
  std::cout << "complex<float>  " << sizeof(std::complex<float>) << "\n";
  std::cout << "complex<double> " << sizeof(std::complex<double>) << "\n";

  return 0;
}

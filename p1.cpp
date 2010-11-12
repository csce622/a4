/**
 *
 * CSCE-622: Generic Programming -- Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 12, 2010
 */

#include <iostream>
#include <boost/mpl/assert.hpp>

using namespace boost;

template <unsigned long N>
struct binary {
  static unsigned const value = binary<N/10>::value << 1 | N%10;
  BOOST_MPL_ASSERT_MSG(N%10<2, INPUT_CONTAINS_DIGITS_OTHER_THAN_0_OR_1, ());
};

template <>
struct binary<0> {
  static unsigned const value = 0;
};

int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p1 # \n";
  std::cout << "######  \n";

  unsigned const one = binary<1>::value;
  unsigned const three = binary<11>::value;
  unsigned const five = binary<101>::value;
  unsigned const seven = binary<111>::value;
  unsigned const nine = binary<1001>::value;

  std::cout << seven << std::endl; 

  std::cout << "We took advantage of the BOOST MPL assertion macros \n";
  std::cout << "to make sure that invocations of the class that maps \n";
  std::cout << "binary number numbers to base 10 integers will \n";
  std::cout << "reject input that contains digits other than 0 or 1. \n";

  std::cout << std::endl;
      
  // The folowing line will be rejected at compilation time.
  //double dummy = binary<007>::value;

  return 0;
}

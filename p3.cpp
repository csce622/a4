/**
 *
 * CSCE-622: Generic Programming -- Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 15, 2010
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits.hpp>


using namespace boost;

template <typename T1, typename T2, typename T3>
typename enable_if<
  mpl::and_<
    is_same<T1, T3>,
    is_same<T2, T3>
  >,
  bool
>::type
add(const std::vector<T1>& x, const std::vector<T2>& y, std::vector<T3>& z) {
  //assert( x.size() == y.size() );
  if ( x.size() != y.size() ) {
    std::cerr << "ERROR in add(): vectors added must have the same size \n";
    return false;
  }
  //assert(&x!=&z); assert(&y!=&z);
  if ( (&x==&z) || (&y==&z) ) {
    std::cerr << "ERROR in add(): input cannot be same as output (vectors passed by reference...) \n";
    return false;
  }
  z.clear();
  typename std::vector<T1>::const_iterator it_x;
  typename std::vector<T2>::const_iterator it_y;
  for (it_x = x.begin(), it_y = y.begin(); it_x < x.end(); it_x++, it_y++) {
    z.push_back(*it_x + *it_y);
  }                            
  return true;
};




int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p3 # \n";
  std::cout << "######  \n";

  std::vector<char> x;
  std::vector<long> y;
  std::vector<long> z;

  // Some code that fills the vectors.
  long myints[] = { -9, 27, 1, 113, 0 };
  char mychars[] = "prout";
  assert(sizeof(myints)/sizeof(long)==(sizeof(mychars)-1)/sizeof(char));
  for (int i = 0; i < sizeof(myints)/sizeof(long); i++) {
    x.push_back(mychars[i]);
    y.push_back(myints[i]);
    z.push_back(100);
  }

  if (!add(z, y, z)) std::cerr << "problem while adding vectors... \n";

  // Print content of the vector z to the screen.
  for (std::vector<long>::iterator it_z = z.begin(); it_z != z.end(); it_z++) {
    std::cout << *it_z << std::endl;
  }

  return 0;
}

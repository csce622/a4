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
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/logical.hpp>

using namespace boost;

template <typename T1, typename T2>
struct greater {
  typedef typename mpl::if_c< 
    !(sizeof(T1) < sizeof(T2)),
    mpl::true_,
    mpl::false_
   >::type type;
  BOOST_MPL_ASSERT_MSG( !(sizeof(T1) < sizeof(T2)), PARTIAL_ORDER_VIOLATED, (T1, T2) );
};

template <typename T1, typename T2, typename T3>
typename enable_if<
  mpl::and_<
    greater<T3, T1>,
    greater<T3, T2>
  >, bool>::type
add(std::vector<T1> x, std::vector<T2> y, std::vector<T3>& z) {
  //assert( x.size() == y.size() );
  if ( x.size() != y.size() ) {
    std::cerr << "ERROR in add(): vectors added must have the same size \n";
    return false;
  }
  
  z.clear();
  typename std::vector<T1>::iterator it_x;
  typename std::vector<T2>::iterator it_y;
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
  long myints[] = { 5, 4, 3, 2, 1 };
  char mychars[] = "abcde";
  assert(sizeof(myints)/sizeof(long)==(sizeof(mychars)-1)/sizeof(char));
  for (int i = 0; i < sizeof(myints)/sizeof(long); i++) {
    x.push_back(mychars[i]);
    y.push_back(myints[i]);
    z.push_back(100);
  }
  
  if (!add(x, y, z)) std::cerr << "problem while adding vectors... \n";
  std::cout << "[+] z after add(x, y, z) " << std::endl;
  for (std::vector<long>::iterator it_z = z.begin(); it_z != z.end(); it_z++) {
    std::cout << "  " << *it_z << std::endl;
  }

  if (!add(x, x, y)) std::cerr << "problem while adding vectors... \n";
  std::cout << "[+] y after add(x, x, y) " << std::endl;
  for (int i = 0; i < y.size(); i++) {
    std::cout << "  " << y[i] << std::endl;
  }

  // Following line will fail at compile time.
  std::cout << "[+] add(y, z, x) cannot compile since partial order is violated" << std::endl;
  //add(y, z, x);
  
  return 0;
}

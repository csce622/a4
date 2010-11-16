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
add(T1 x, T2 y, T3 z) {
  return false;
};




int main(int,char*[])
{
  std::cout << "  ######\n";
  std::cout << " # p3 # \n";
  std::cout << "######  \n";

  std::vector<char> x;
  std::vector<long> y;
  std::vector<long> z;

  // Filling the vectors.
  long myints[] = { -9, 27, 1, 113, 0 };
  char mychars[] = "prout";
  assert(sizeof(myints)/sizeof(long)==(sizeof(mychars)-1)/sizeof(char));
  for (int i = 0; i < sizeof(myints)/sizeof(long); i++) {
    x.push_back(mychars[i]);
    y.push_back(myints[i]);
    z.push_back(100);
  }



  return 0;
}

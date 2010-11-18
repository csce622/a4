/**
 *
 * @title add.hpp
 *
 * @brief generic function add takes three std::vector as its parmaters; first
 * two are used as input, the third as an output.  The function performs an
 * elementwise addition of the two input vectors, and write the result into
 * the output vector.
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 18, 2010
 */

#ifndef ADD_HPP
#define ADD_HPP

#include <vector>
#include <boost/utility.hpp>

#include "greater.hpp"

using namespace boost;

template <typename T1, typename T2, typename T3>
typename enable_if<
  mpl::and_<
    greater<T3, T1>,
    greater<T3, T2>
    >, 
    bool
  >::type
add(std::vector<T1> x, std::vector<T2> y, std::vector<T3>& z) {

  if ( x.size() != y.size() ) {
    std::cerr << "ERROR in add(): vectors added must have the same size \n";
    return false;
  }
  //assert( x.size() == y.size() );
  
  z.clear();

  typename std::vector<T1>::iterator it_x;
  typename std::vector<T2>::iterator it_y;
  for (it_x = x.begin(), it_y = y.begin(); it_x < x.end(); it_x++, it_y++) {
    z.push_back(*it_x + *it_y);
  }

  return true;
};

#endif // ADD_HPP

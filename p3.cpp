/**
 *
 * @title p3.cpp
 *
 * @brief CSCE-622: Generic Programming -- Assignment 4
 *
 * @author Damien L-G <lebrungd@neo.tamu.edu>
 * @date November 15, 2010
 */

#include <iostream>
#include <cassert>
#include <vector>

#include "add.hpp"

using namespace boost;

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
  
  std::cout << "[+] z after add(x, y, z) " << std::endl;
  if (!add(x, y, z)) std::cerr << "problem while adding vectors... \n";
  for (std::vector<long>::iterator it_z = z.begin(); it_z != z.end(); it_z++) {
    std::cout << "  " << *it_z << std::endl;
  }

  std::cout << "[+] y after add(x, x, y) " << std::endl;
  if (!add(x, x, y)) std::cerr << "problem while adding vectors... \n";
  for (int i = 0; i < y.size(); i++) {
    std::cout << "  " << y[i] << std::endl;
  }

  // Following line will fail at compile time.
  //add(y, z, x);
  std::cout << "[+] add(y, z, x) cannot compile since partial order is violated" << std::endl;
  
  return 0;
}

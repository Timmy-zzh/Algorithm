#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <queue>
// #include "src/bean.h"

#include <random>
#include <algorithm>

/**************************** 《C++ Primer Plus》 ******************************** */

int main()
{
  std::cout << "《C++ Primer Plus》" << std::endl;

  // int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int months[12];
  months[1] = 31;
  months[2] = 28;
  months[3] = 31;

  std::cout << "months[1]:" << months[1] << std::endl;
  std::cout << "months[2]:" << months[2] << std::endl;

  std::cout << "size of months array = " << sizeof(months) << std::endl;
  std::cout << " size of one elelment :" << sizeof(months[0]) << std::endl;
  std::cout << " number of elements :" << sizeof(months) / sizeof(months[0]) << std::endl;

  return 0;
}
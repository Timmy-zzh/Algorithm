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

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

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

  // vector<string> matrix = {"10100", "10111", "11111", "10010"};

  // for (auto ele : matrix)
  // {
  //   std::cout << ele << ",";
  // }
  // std::cout << std::endl;

  // auto res = maximalRectangle(matrix);

  // std::cout << "res:" << res << std::endl;

  // 遍历1维数组
  // for (auto ele : res)
  // {
  //   std::cout << ele << ",";
  // }
  // std::cout << std::endl;

  // 遍历2维数组
  // for (vector<int> ele : res)
  // {
  //     for (auto element : ele)
  //     {
  //         std::cout << element << ",";
  //     }
  //     std::cout << std::endl;
  // }
  // std::cout << std::endl;

  return 0;
}
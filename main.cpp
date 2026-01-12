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

/**
LCR 072. x 的平方根
https://leetcode.cn/problems/jJ0w9p/description/

给定一个非负整数 x ，计算并返回 x 的平方根，即实现 int sqrt(int x) 函数。
正数的平方根有两个，只输出其中的正数平方根。
如果平方根不是整数，输出只保留整数的部分，小数部分将被舍去。

示例 1：
输入: x = 4
输出: 2

示例 2：
输入: x = 8
输出: 2
解释: 8 的平方根是 2.82842...，由于小数部分将被舍去，所以返回 2

提示：
0 <= x <= 231 - 1
注意：本题与主站 69 题相同： https://leetcode.cn/problems/sqrtx/
 */
int mySqrt(int x)
{
  int left = 1;
  int right = x;
  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    if (mid == x / mid)
    {
      return mid;
    }

    if (mid > x / mid)
    {
      // 前一个数字小于
      if (mid - 1 < x / (mid - 1))
      {
        return mid - 1;
      }
      right = mid - 1;
    }
    else
    {
      left = mid + 1;
    }
  }
  return 0;
}

/**
 * 1、审题：
 * - 输入一个非负整数x，也就是0或者正整数，要计算x的开平方根后的结果，如果结果带有小数，则只取整数部分
 * 2、解题：
 * - 普通循环解法：遍历从1到x/2的部分，判断当前遍历的数i的平方大于x，而前面数字i-1的平方小于等于x，则命中
 * - 二分查找法：使用左右指针left=1，right=n，判断中间mid的平方是否登录x
 * - 如果不等于，判断mid*mid》n，且mid-1的平方《=n，则mid-1未目标值，如果mid平方小于n，说明目标值在右侧，left=mid+1
 * - 否则mid-1的平方也大于n，则目标值在左侧范围，right=mid-1
 * -- 要考虑int类型值表示范围
 */
int mySqrt1(int x)
{
  int res = 0;
  for (int i = 1; i <= x; i++)
  {
    if (i == x / i)
    {
      return i;
    }
    else if (i > x / i)
    {
      return i - 1;
    }
  }
  return res;
}

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
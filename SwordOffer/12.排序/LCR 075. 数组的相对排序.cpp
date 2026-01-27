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
 * - 脑子得练才行，光看书，不动手写，那不行！效果打/home/yingzi/zzh_work/github/Algorithm/SwordOffer/12.排序/LCR 075. 数组的相对排序.cpp骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
LCR 075. 数组的相对排序
https://leetcode.cn/problems/0H97ZC/description/

给定两个数组，arr1 和 arr2，
arr2 中的元素各不相同
arr2 中的每个元素都出现在 arr1 中
对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。
未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。

示例：
输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]

提示：
1 <= arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
arr2 中的元素 arr2[i] 各不相同
arr2 中的每个元素 arr2[i] 都出现在 arr1 中
 */

/**
 * 1、审题：
 * - 输入两个数组，其中arr2数组的所有元素在arr1中都有出现，且arr2中的元素不重复
 * - 要求arr1中的元素要求按照arr2中的元素进行重新排序，其他的元素按照升序排序
 * 2、解题：计数法
 * - 题目的条件是元素大小范围为[0,1000],可准备一个计数数组counts[1001],计算arr1数组中每个元素出现的次数
 * - 再遍历arr2，根据arr2数组的元素将arr1中的元素重新排序，然后剩下的元素按照升序排序，
 * - 通过counts计数数组不断计算元素出现的次数
 */
vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2)
{
  std::vector<int> res;
  std::vector<int> counts(1001, 0);

  for (int item : arr1)
  {
    counts[item]++;
  }

  // 遍历arr2
  for (int item : arr2)
  {
    while (counts[item] > 0)
    {
      res.push_back(item);
      counts[item]--;
    }
  }

  // 继续遍历counts，将剩下的元素升序遍历出来
  for (int i = 0; i <= 1000; i++)
  {
    int count = counts[i];
    while (count > 0)
    {
      res.push_back(i);
      count--;
    }
  }
  return res;
}

int main()
{
  std::cout << "《C++ Primer Plus》" << std::endl;

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
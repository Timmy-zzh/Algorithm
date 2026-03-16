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
#include "src/bean.h"
#include <random>
#include <algorithm>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LCR 080. 组合
https://leetcode.cn/problems/uUsW3B/description/
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

示例 1：
输入: n = 4, k = 2
输出:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

示例 2：
输入: n = 1, k = 1
输出: [[1]]

提示：
1 <= n <= 20
1 <= k <= n
 */

void helper(int n, int k, int index, vector<int> &item, vector<vector<int>> &res)
{
  if (item.size() == k)
  {
    res.push_back(item);
    return;
  }
  if (index > n)
  {
    return;
  }
  helper(n, k, index + 1, item, res);

  item.push_back(index);
  helper(n, k, index + 1, item, res);
  item.pop_back();
}

/**
 * 1、审题：输入两个数字n和k，现在要求在[1,n]的范围内，选择k个数字组成子集并返回
 * 2、解题：
 * - 采用回溯算法，面对遍历到的数字，有两种选择添加到当前子集中，或不添加
 * - 添加的话遍历完成后需要删除，
 * - 直到当前子集的个数等于k，即终止递归处理
 */
vector<vector<int>> combine(int n, int k)
{
  vector<vector<int>> res;
  vector<int> item;
  if (n == k)
  {
    for (int i = 1; i <= n; i++)
    {
      item.push_back(i);
    }
    res.push_back(item);
    return res;
  }

  helper(n, k, 1, item, res);
  return res;
}

int main()
{
  std::cout << "《剑指offer》" << std::endl;
  ListNode node1(4);
  ListNode node2(2);
  ListNode node3(1);
  ListNode node4(3);

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node1.print();

  // auto res = sortArray(nums);
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
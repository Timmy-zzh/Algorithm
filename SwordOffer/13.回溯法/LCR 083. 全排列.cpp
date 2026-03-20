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
LCR 083. 全排列
https://leetcode.cn/problems/VvJkup/description/

给定一个不含重复数字的整数数组 nums ，返回其 所有可能的全排列 。可以 按任意顺序 返回答案。

示例 1：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

示例 2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]

示例 3：
输入：nums = [1]
输出：[[1]]

提示：
1 <= nums.length <= 6
-10 <= nums[i] <= 10
nums 中的所有整数 互不相同
 */

/**
 * 前面采用的广度优先算法思想，每次遍历都要对原始数组进行全部遍历，并判断哪些元素遍历过，接着进行过滤
 * 现在采用阶乘算法，全排列每次选中的元素，第一次从数组中n个元素选择其中一个元素，可以是任何一个元素n个选择情况
 * - 第二个元素从剩下的n-1个元素中选择，最后到第n个元素选择时只有一个选项
 * - 采用递归算法，每次从数组中选择一个元素，数组可选的元素越来越少，并且通过swap元素交换来定位选中的元素，最后放到结果中
 */
void swapEle(vector<int> &nums, int i, int j) // 数组元素交换
{
  if (i != j)
  {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
  }
}

void helper1(vector<int> &nums, int index, vector<vector<int>> &res)
{
  if (index == nums.size())
  {
    res.push_back(nums);
    return;
  }

  for (int i = index; i < nums.size(); i++)
  {
    // 交换
    swapEle(nums, i, index);

    helper1(nums, index + 1, res);

    swapEle(nums, i, index);
  }
}

vector<vector<int>> permute(vector<int> &nums)
{
  vector<vector<int>> res;

  helper1(nums, 0, res);

  return res;
}

/**
 * 1、审题：输入一个不包含重复元素的整数，要求该数组的所有排列数组
 * 2、解题：使用递归函数进行回溯算法实现
 * - 也可以说是深度优先遍历
 * - 从数组中选取一个元素添加到集合中，每次都需要遍历所有的元素，为了防止重复添加，需要使用一个数组来标记是否已经添加过
 * - 如果已经添加过则进行过滤处理
 */
void helper(vector<int> &nums, int count, vector<bool> &visited, vector<int> &item, vector<vector<int>> &res)
{
  if (count == nums.size())
  {
    res.push_back(item);
    return;
  }

  // 遍历所有的元素
  for (int i = 0; i < nums.size(); i++)
  {
    // 过滤已经遍历过了的元素
    if (!visited[i])
    {
      visited[i] = true;
      item.push_back(nums[i]);
      helper(nums, count + 1, visited, item, res);
      item.pop_back();
      visited[i] = false;
    }
  }
}

vector<vector<int>> permute1(vector<int> &nums)
{
  vector<bool> visited(nums.size());
  vector<vector<int>> res;
  vector<int> item;
  helper(nums, 0, visited, item, res);
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
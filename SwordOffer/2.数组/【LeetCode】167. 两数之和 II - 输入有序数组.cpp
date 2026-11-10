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
#include <unordered_set>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。写就是思考
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LeetCode 167. 两数之和 II - 输入有序数组
https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description/

给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列。
请你从数组中找出满足相加之和等于目标数 target 的 两个 数。令这两个数分别是 numbers[index1] 和 numbers[index2] ，其中 1 <= index1 < index2 <= numbers.length 。
以长度为 2 的整数数组 [index1, index2] 的形式返回这两个整数的下标 index1 和 index2。
你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。
你所设计的解决方案必须只使用常数级的额外空间。

示例 1：
输入：numbers = [2,7,11,15], target = 9
输出：[1,2]
解释：2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。

示例 2：
输入：numbers = [2,3,4], target = 6
输出：[1,3]
解释：2 与 4 之和等于目标数 6 。因此 index1 = 1, index2 = 3 。返回 [1, 3] 。

示例 3：
输入：numbers = [-1,0], target = -1
输出：[1,2]
解释：-1 与 0 之和等于目标数 -1 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。

提示：
2 <= numbers.length <= 3 * 104
-1000 <= numbers[i] <= 1000
numbers 按 非递减顺序 排列
-1000 <= target <= 1000
仅存在一个有效答案
 */

/**
 * 双指针解法：
 * - 题目给出的数组是元素递增数组，可以采用递增数组的特性，使用双指针，默认left指向元素下标0，right指向数组下标size-1元素
 * - 判断他们的和是否等于目标值，如果相等就返回left，right的数组
 * - 如果他们的和不等于目标值，如果和大于目标值大小，则right--右侧指针左移将他们的和减少；否则left=++左侧指针右移让和增大
 */
vector<int> twoSum(vector<int> &numbers, int target)
{
  int size = numbers.size();
  int left = 0;
  int right = size - 1;
  int sum = 0;
  while (left < right)
  {
    sum = numbers[left] + numbers[right];
    if (sum == target)
    {
      return {left + 1, right + 1};
    }
    else if (sum > target)
    {
      right--;
    }
    else
    {
      left++;
    }
  }

  return {};
}

/**
 * 1、审题：输入一个递增整数数组和一个目标值target，要求从数组中找出两个不重复非元素，两个元素的和等于目标值target，并最终返回这两个元素的下标值
 * 2、解题：暴力解法
 * - 两层for循环让数组中每个元素都能与其他元素两两相加，求他们的和，判断是否等于目标值target
 * 3、时间复杂度：n^2,超出时间限制
 */
vector<int> twoSum1(vector<int> &numbers, int target)
{
  int size = numbers.size();
  for (int i = 0; i < size; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      if ((numbers[i] + numbers[j]) == target)
      {
        return {i + 1, j + 1};
      }
    }
  }
  return {};
}

int main()
{
  std::cout << "《剑指》" << std::endl;
  // vector<string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  // auto res = maxProduct(words);
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
  //   for (auto element : ele)
  //   {
  //     std::cout << element << ",";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  // std::cout << "map +++++++++++++++ " << std::endl;
  // for (auto ele : map)
  // {
  //   std::cout << ele.first << " ---- nextNodes: " << std::endl;
  //   for (auto ele : ele.second)
  //   {
  //     std::cout << ele;
  //     std::cout << std::endl;
  //   }

  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  // std::cout << "inDegreeMap ============ " << std::endl;
  // for (auto ele : inDegreeMap)
  // {
  //   std::cout << ele.first << " ---- " << ele.second;
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  return 0;
}
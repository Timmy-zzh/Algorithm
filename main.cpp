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
LCR 119. 最长连续序列
https://leetcode.cn/problems/WhsWhI/description/

给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

示例 1：
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

示例 2：
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9

提示：
0 <= nums.length <= 104
-109 <= nums[i] <= 109

进阶：可以设计并实现时间复杂度为 O(n) 的解决方案吗？
 */
int longestConsecutive(vector<int> &nums)
{
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
  vector<string> words = {"tars", "rats", "arts", "star"};

  // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
  // vector<vector<int>> prerequisites = {
  //     {1, 0},
  //     {2, 0},
  //     {3, 1},
  //     {3, 2},
  // };

  // vector<int> nums = {1, 2, 3};
  // vector<vector<int>> isConnected = {
  //     {1, 0, 0, 1},
  //     {0, 1, 1, 0},
  //     {0, 1, 1, 1},
  //     {1, 0, 1, 1},
  // };
  // vector<vector<int>> isConnected = {
  //     {1, 1, 0},
  //     {1, 1, 0},
  //     {0, 0, 1},
  // };

  auto res = numSimilarGroups(words);
  std::cout << "res:" << res << std::endl;

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
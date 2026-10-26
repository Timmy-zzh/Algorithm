#include "src/bean.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。写就是思考
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * --
 * 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LeetCode 15. 三数之和
https://leetcode.cn/problems/3sum/description/

给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i !=
j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0
。请你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。

示例 1：
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。

示例 2：
输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。

示例 3：
输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。
 */

/**
 * 双指针解法
 * -该题是之前两数之和的升级版，先对数组进行排序，从数组中找出下标分别为i，j，k，并且他们的顺序是递增的
 * -先从i开始，i元素固定，然后在后面的[i+1,n-1]范围内找出两个元素的和等于-nums[i]的大小，并且该范围的数组已经是递增的了，这个操作和之前的求两数之和的操作一样的了
 * -- 可以采用双指针解法来实现
 * -接下来就是过滤重复子数组的情况，需要在排序后的数组中过滤掉后一位元素与当前元素值相同的元素即可
 */
vector<vector<int>> threeSum(vector<int> &nums) {
  vector<vector<int>> res;
  int size = nums.size();
  // 为数组nums排序
  std::sort(nums.begin(), nums.end());

  int i = 0;
  int j = 0;
  int k = 0;
  while (i < size) {
    while (i > 0 && (i < size) &&
           (nums[i] == nums[i - 1])) { // 过滤与前一个相同的元素
      i++;
    }
    if (i >= size) {
      break;
    }

    // 从 i+1到 size-1范围寻找两个元素位置j,k,使得他们的和等于 -nums[i] 的大小，
    j = i + 1;
    k = size - 1;
    int target = -(nums[i]);
    while (j < k) {
      int sum = nums[j] + nums[k];
      if (sum == target) {
        res.push_back({nums[i], nums[j], nums[k]});
        j++;
        while (j < size && (nums[j] == nums[j - 1])) { // 过滤与前一个相同的元素
          j++;
        }
        k--;
      } else if (target > sum) {
        j++;
      } else {
        k--;
      }
    }
    i++;
  }
  return res;
}

/**
 * 1、审题：输入一个整数数组，要求从数组中找出三个元素，最终三个元素的和为0，这样的三个元素存在多个，返回他们组成的数组
 * 2、解题：
 * 暴力解法
 * -
 * 使用三层for循环，让每一个都能与其他两个元素进行相加，并求最后三个元素的和是否等于0
 */
vector<vector<int>> threeSum1(vector<int> &nums) {
  vector<vector<int>> res;
  int size = nums.size();
  // 为数组nums排序
  std::sort(nums.begin(), nums.end());

  for (int i = 0; i < size; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    for (int j = i + 1; j < size; j++) {
      if (j > i + 1 && nums[j] == nums[j - 1]) {
        continue;
      }
      for (int k = j + 1; k < size; k++) {
        if (k > j + 1 && nums[k] == nums[k - 1]) {
          continue;
        }
        if (nums[i] + nums[j] + nums[k] == 0) {
          res.push_back({nums[i], nums[j], nums[k]});
        }
      }
    }
  }

  return res;
}

int main() {
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
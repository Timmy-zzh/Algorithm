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
【LeetCode】209. 长度最小的子数组
https://leetcode.cn/problems/minimum-size-subarray-sum/description/

给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ...,
numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

示例 1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。

示例 2：
输入：target = 4, nums = [1,4,4]
输出：1

示例 3：
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0

提示：
1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104

进阶：
如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n))
时间复杂度的解法。
 */

/**
 * 1、审题：输入一个正整数数组和一个整数值target，要求从数组中找出一个最短子数组，子数组的和大于等于target的值，并返回子数组的长度
 * 2、解题：使用双指针解法l-r，刚开始左右指针都指向数组最左侧元素，然后判断双指针指向的子数组的和大小sum，如果和大于等于target的值，
 * - 求他们子数组的长度，并且让左指针left左移一位继续比较
 * - 如果小于target的值，则右指针往右移，扩大sum和的大小，直到数组的最右侧
 * 3、总结：
 * - 子数组长度，要比对的是最小长度，所以默认值应该要是大的值
 * - 存在子数组命中长度刚好是数组原始长度，所以res默认值要找一个不存在的值
 * 4、题外话：
 * - 如果数组中存在负数呢？
 */
int minSubArrayLen(int target, vector<int> &nums) {
  int left = 0, right = 0;
  int res = nums.size() + 1;
  int sum = nums[left];

  while (left <= right && right < nums.size()) {
    std::cout << " left:" << left << " ,right:" << right << " ,sum:" << sum
              << " ,res:" << res << std::endl;
    if (sum >= target) {
      res = min(res, (right - left + 1));
      sum -= nums[left];
      left++;
    } else {
      right++;
      if (right < nums.size()) {
        sum += nums[right];
      }
    }
  }
  return res > nums.size() ? 0 : res;
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
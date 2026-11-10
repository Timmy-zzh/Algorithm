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
【LeetCode】713. 乘积小于 K 的子数组
https://leetcode.cn/problems/subarray-product-less-than-k/description/

给定一个整数数组 nums 和一个整数 k。
请你返回 子数组 内所有元素的 乘积严格小于 k 的连续子数组的数目。

示例 1：
输入：nums = [10,5,2,6], k = 100
输出：8
解释：8 个乘积小于 100
的子数组分别为：[10]、[5]、[2]、[6]、[10,5]、[5,2]、[2,6]、[5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于 100 的子数组。

示例 2：
输入：nums = [1,2,3], k = 0
输出：0

提示:
1 <= nums.length <= 3 * 104
1 <= nums[i] <= 1000
0 <= k <= 106
 */

/**
 * 双指针解法的另一种实现：
 * -
 * 使用while循环，让左右指针left，right在循环中的子数组乘积值，默认两个指针都指向第一个元素，他们的乘积值也是第一个元素值
 * -
 * 然后判断乘积值与目标值k的大小，如果比k大则移动左指针，并且乘积处于原先的左指针元素值
 * -
 * 如果乘积值小于目标值k，则累加子数组个数，并将右指针元素右移，直到左指针移动到数组最右侧
 */
int numSubarrayProductLessThanK(vector<int> &nums, int k) {
  int res = 0;
  int left = 0, right = 0;
  int mult = nums[0];

  while (left <= right && left < nums.size()) {
    std::cout << "left:" << left << " ,right:" << right << " ,mult:" << mult
              << std::endl;

    if (mult < k) {
      res++;
      right++;
      if (right < nums.size()) {
        mult *= nums[right];
      } else {
        left++;
        right = left;
        if (left < nums.size())
          mult = nums[left];
      }
    } else {
      left++;
      right = left;
      if (left < nums.size())
        mult = nums[left];
    }
  }

  return res;
}

/**
 * 1、审题：输入一个整数数组nums，和整数值k，要求从数组中找出所有的子数组，要求子数组中所有元素的乘积小于整数k，返回所有的子数组的个数
 * 2、解题：双指针解法
 * -
 * 使用双指针left，和right，left从原始数组最左侧位置开始，right指针默认与left指针位置相同，且他们的乘积为子数组第一个元素的值，
 * -
 * 接着比较乘积与目标值k的大小，如果乘积小于目标值k，则有指针right右移一位，乘积也变大，直到他们的乘积大于等于目标值k，则本次left循环结束
 * - 下一轮循环从left+1位置继续求子数组的乘积值
 */
int numSubarrayProductLessThanK1(vector<int> &nums, int k) {

  int res = 0;
  int sum = 1;
  int size = nums.size();
  for (int left = 0; left < size; left++) {
    for (int right = left; right < size; right++) {
      if (left == right) {
        sum = nums[right];
      } else {
        sum *= nums[right];
      }

      if (sum < k) {
        res++;
      } else {
        break;
      }
    }
  }
  return res;
}

int main() {
  std::cout << "《剑指》" << std::endl;
  vector<int> nums = {10, 5, 2, 6};
  int k = 100;
  auto res = numSubarrayProductLessThanK(nums, k);
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
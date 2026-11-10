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
【LeetCode】560. 和为 K 的子数组
https://leetcode.cn/problems/subarray-sum-equals-k/description/

给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k
的子数组的个数 。 子数组是数组中元素的连续非空序列。

示例 1：
输入：nums = [1,1,1], k = 2
输出：2

示例 2：
输入：nums = [1,2,3], k = 3
输出：2

提示：
1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107
 */

/**
 * 不要双层for循环，使用map保存当前遍历的子数组的的和，使用map保存和作为key值，count为子数组和的个数
 * 默认只有一个和为0，count为1的map值，
 * 然后不断遍历子数组，累加遍历元素的和得到sum值，然后计算sum-k
 * 这个值是否在map中，存在的话，则目标count值增加1
 * - 疑问：
 *  - 没明白为何不是将sum值添加到map中后，再来计算sum-k的个数了？
 *  - 每次遍历，都要从map中寻找寻找sum-k值的个数
 */
int subarraySum(vector<int> &nums, int k) {
  int res = 0;
  int sum = 0;
  // std::map<int, int> sumCount(0, 1);
  std::map<int, int> sumCount;
  sumCount[0] = 1;

  for (int i = 0; i < nums.size(); i++) {
    sum += nums[i];

    // 每次遍历，都计算sum-k是否在map中是否存在，存在的话，则将该count值累加起来
    if (sumCount.find(sum - k) != sumCount.end()) {
      res += sumCount[sum - k];
    }

    // 再将sum值添加到map中去
    int count = 0;
    if (sumCount.find(sum) != sumCount.end()) {
      count = sumCount[sum];
    }
    sumCount[sum] = count + 1;
  }
  return res;
}

/**
 * 1、审题：输入一个数组和一个目标值，需要从数组中找出和等于目标值k的子数组个数
 * 2、解题：暴力解法
 * -
 * 双层for循环，遍历所有的子数组，并求子数组的和，等于目标值k，则子数组个数值增加1
 * 3、时间复杂度：n^2
 * 4、总结：
 * - 双层for循环，计算次数太多了，需要优化
 */
int subarraySum1(vector<int> &nums, int k) {
  int res = 0;
  int size = nums.size();
  int sum = 0;

  for (int i = 0; i < size; i++) {
    for (int j = i; j < size; j++) {
      if (i == j) {
        sum = nums[i];
      } else {
        sum += nums[j];
      }

      if (sum == k) {
        res++;
      }
    }
  }
  return res;
}

int main() {
  std::cout << "《剑指》" << std::endl;
  vector<int> nums = {10, 5, 2, 6};
  int k = 100;
  auto res = subarraySum(nums, k);
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
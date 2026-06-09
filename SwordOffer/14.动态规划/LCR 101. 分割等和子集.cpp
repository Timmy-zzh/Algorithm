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
LCR 101. 分割等和子集
https://leetcode.cn/problems/NUPfPr/description/

给定一个非空的正整数数组 nums ，请判断能否将这些数字分成元素和相等的两部分。

示例 1：
输入：nums = [1,5,11,5]
输出：true
解释：nums 可以分割成 [1, 5, 5] 和 [11] 。

示例 2：
输入：nums = [1,2,3,5]
输出：false
解释：nums 不可以分为和相等的两部分

提示：
1 <= nums.length <= 200
1 <= nums[i] <= 100
 */

/**
 * 使用动态规划解法,先找状态转移方程式
 * - 使用二维数组dp[i][t]=bool 用于计算一共前i个元素，能够找到满足总元素累加和的一般的值 t=sum/2
 * - 最后的结果为dp[i][t]
 * - 其中第一列 dp[i][0] 表示不管集合元素，要求他的子数组累加和都为0，可以选择一个元素都不选，则dp[i][0]全部为true
 * - 第一行数据 dp[0][j] 表示一个元素都没有，要去的子数组累加和为t，不存在这种情况，dp[0][j] 等于false
 * - 中间的元素 dp[i][j] 存在两种情况，如果他不选择当前第i个元素，则他的值依赖于 =dp[i-1][j]的值
 * -- 也可以选中第i个元素，则它的值等于 =dp[i-1][j-nums[i][j]]
 */
bool canPartition(vector<int> &nums)
{
  int n = nums.size();
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum += nums[i];
  }

  if (sum % 2 == 1)
  {
    return false; // 奇数直接返回false
  }

  int t = sum / 2;
  vector<vector<bool>> dp(n, vector<bool>(t + 1, false));
  for (int i = 0; i < n; i++) // 处理第一列
  {
    dp[i][0] = true;
  }

  for (int i = 1; i < n; i++) // 处理从第二列开始的元素
  {
    for (int j = 1; j <= t; j++)
    {
      dp[i][j] = dp[i - 1][j];
      if (!dp[i][j] && j >= nums[i])
      {
        dp[i][j] = dp[i - 1][j - nums[i]];
      }
    }
  }

  return dp[n - 1][t];
}

/**
 * 1、审题： 输入一个数组，可以知道数组中所有元素的和，要求从数组中找出一个子数组，这个子数组的和等于整个数组和的一半，存在的话返回true值
 * 2、解题：
 * - 可以使用回溯法，找出所有符合要求的子数组的情况，存在一个就可以返回结果值bool，但是这种算法浪费多余计算操作
 * - 改为使用动态规划，状态转移方程式
 * - 先求出数组中所有元素的和 sum，他的一半就是sum/2,假设其值为t
 * - 因为涉及到两个因素：也即是从i个元素的数组中，找出累加值值为t，也就是求f(i,t)的结果值boo类型
 * - 采用倒序遍历方法，第i个元素也就是arr[i-1]这个值，对计算有两种选择方式，第一种是加入当前计数，将该值放到预选子数组中，
 * - 则它的值依赖于前一个元素的处理结果 f(i,t) = f(i-1, t-nums[i-1]), 也就是前面i-1个元素，其从中选择的子数组，累加和等于t-nums[i-1]命中的话也行
 * -- 第二种是不加入当前计算，则 f(i,t) = f(i-1,t); 要求在i-1个元素中，选择和为t的子数组
 * - 直到遍历到第一个元素，也有两种情况，也就是遍历到最后一个元素时，要求他的累计值为0，他的值一定为true， f(0,0)=true;
 * - 如果遍历到第一个元素了，要求的累加值还是大于0的，那他的值一定是false
 */

bool helper(vector<int> &nums, vector<vector<bool>> &dp, int i, int t)
{
  std::cout << "i:" << i << " ,t:" << t << " ,dp[i][t]:" << dp[i][t] << std::endl;
  if (dp[i][t])
  {
    return true;
  }
  if (t == 0)
  {
    dp[i][t] = true;
  }
  else if (i == 0)
  {
    dp[i][t] = false;
  }
  else
  {
    // 第i个元素，不添加到当前计算
    dp[i][t] = helper(nums, dp, i - 1, t);
    // 添加
    if (!dp[i][t] && t >= nums[i - 1]) // 边界控制
    {
      dp[i][t] = helper(nums, dp, i - 1, t - nums[i - 1]);
    }
  }
  std::cout << "---i:" << i << " ,t:" << t << " ,dp[i][t]:" << dp[i][t] << std::endl;
  return dp[i][t];
}

bool canPartition1(vector<int> &nums)
{
  int n = nums.size();
  int sum = 0;
  for (size_t i = 0; i < n; i++)
  {
    sum += nums[i];
  }

  // 累加和奇数的不满足条件
  if (sum % 2 == 1)
  {
    return false;
  }

  int t = sum / 2;
  // 使用动态规划
  vector<vector<bool>> dp(n + 1, vector<bool>(t + 1, false));

  // 递归写法
  return helper(nums, dp, n, t);
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // vector<int> nums = {1, 5, 11, 5};
  vector<int> nums = {2, 2, 1, 1};

  auto res = canPartition(nums);
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
  //     for (auto element : ele)
  //     {
  //         std::cout << element << ",";
  //     }
  //     std::cout << std::endl;
  // }
  // std::cout << std::endl;

  return 0;
}
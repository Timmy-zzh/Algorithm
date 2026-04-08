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
LCR 089. 打家劫舍
https://leetcode.cn/problems/Gu0c2T/description/

一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响小偷偷窃的唯一制约因素
就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组 nums ，请计算 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

示例 1：
输入：nums = [1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。

示例 2：
输入：nums = [2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 400
 */

/**
 * 1、审题：
 * - 输入一个int数组，数组中的每个元素表示一个房屋中存放的金钱数目，现在有一个小偷想去這些房屋中偷盗
 * - 因为存在防监控系统，如果连续偷盗两家挨着的房屋，则会触发警报，要求在不触发警报的情况下小偷能够偷盗的最大金额并返回
 * 2、解题：动态规划解法
 * - 使用动态规划解法，先找到状态转移方程式，假设f(i)表示小偷经过第i个房间时，能够偷盗的最多金额钱财
 * - 则存在两种情况：第一是第i个房间被偷，则他偷盗金额值为 f(i-2)+nums[i]
 *  -- 第二情况是第i个房间不偷，则的金额是前面i-1个房间的金额， 则两种情况的比较后的最大值为所求
 * - 则状态转移方程式为： f(i) = max(f(i-2)+nums[i] , f(i-1))
 * -- 其中f(0)=nums[0]; f(1) = max(nums[0],nums[1]);
 * 3、通过递归函数实现，
 */
void helper(vector<int> &nums, int i, vector<int> &dp)
{
  if (i == 0)
  {
    dp[0] = nums[0];
  }
  else if (i == 1)
  {
    dp[1] = max(nums[1], nums[0]);
  }
  else if (dp[i] < 0)
  {
    helper(nums, i - 2, dp);
    helper(nums, i - 1, dp);
    dp[i] = max((dp[i - 2] + nums[i]), dp[i - 1]);
  }
}

int rob(vector<int> &nums)
{
  int n = nums.size();
  vector<int> dp(n, -1);

  helper(nums, n - 1, dp);
  return dp[n - 1];
}

int main()
{
  std::cout << "《剑指》" << std::endl;
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
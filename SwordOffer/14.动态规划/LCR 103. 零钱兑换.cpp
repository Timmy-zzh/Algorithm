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
LCR 103. 零钱兑换
https://leetcode.cn/problems/gaM7Ch/description/

给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
你可以认为每种硬币的数量是无限的。

示例 1：
输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1

示例 2：
输入：coins = [2], amount = 3
输出：-1

示例 3：
输入：coins = [1], amount = 0
输出：0

示例 4：
输入：coins = [1], amount = 1
输出：1

示例 5：
输入：coins = [1], amount = 2
输出：2

提示：
1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
 */

/**
 * 使用一维数组实现状态方程
 */
int coinChange(vector<int> &coins, int amount)
{
  vector<int> dp(amount + 1, amount + 1);
  dp[0] = 0;

  for (int i = 0; i < coins.size(); i++)
  {
    for (int j = coins[i]; j <= amount; j++)
    {
      dp[j] = min(dp[j], dp[j - coins[i]] + 1);
    }
  }

  return dp[amount] > amount ? -1 : dp[amount];
}

/**
 * 动态规划解法: 无限背包问题
 * - 状态转移方程式：要求在coins整数数组中取出最少个数的硬币，这些硬币的总额等于amout
 * - 使用表达式 f(i，j) 为使用数组coins前i个元素，来凑齐总额为j时的最少得硬币个数
 * - 则对于第i个硬币可以有不同的选择，选择不使用第i个硬币，则 f(i,j) = f(i-1,j);
 * - 也可以选择使用1个第i个元素，则 f(i,j) = f(i-1,j - coins[i-1])
 * - 也可选择使用2,3，。。n个元素，则 f(i,j) = f(i-1, j - n*coins[i-1])
 * 可以得到表达式： f(i,j) = f(i-1, j - n*conins[i-1] ) ( n*conins[i-1] <= j )
 * 其中 f(0,0)=0;
 * & 使用二位数组dp[i][j] 来表示使用coins数组前i个元素，组成总额j的最少硬币个数
 * - 其中dp[0][0] = 0, 其他默认值为 target+1，表示不存在结果值
 * - dp[i][j] = min( dp[i][j] , dp[i-1][j-k*coins[i-1]]+k ) 其中k的个数要求k*conins[i-1] <= j
 * & 优化处理
 */
int coinChange2(vector<int> &coins, int amount)
{
  int n = coins.size();
  vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));

  dp[0][0] = 0;

  // 多个元素，其总额等于0的话，其结果等于0
  for (int i = 1; i <= n; i++)
  {
    dp[i][0] = 0;
  }

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= amount; j++)
    {
      for (int k = 0; k * coins[i - 1] <= j; k++)
      {
        if (dp[i - 1][j - k * coins[i - 1]] <= amount)
        {
          dp[i][j] = min(dp[i][j], dp[i - 1][j - k * coins[i - 1]] + k);
        }
      }
    }
  }

  return dp[n][amount] > amount ? -1 : dp[n][amount];
}

/**
 * 1、审题：
 * - 输入一个数组表示硬币的面额，和一个正整数amount，要求从硬币数组中选取若干个硬币，要求选取的硬币总面额大小等于amount
 * - 求组成目标面额，最少需要的硬币个数并返回，如果没有满足条件的硬币则返回-1，注意数组中的每个硬币可以无限使用多次
 * 2、解题：
 * 回溯法：
 * - 使用递归函数，不断从数组中使用一个元素（可重复获取），然后从总面额amount中减掉，直到amount<=0,
 * -- amount=0则命中了，并比较最少实用硬币个数
 */
void helper(vector<int> &coins, int amount, int index, int useAcount, int &resAcount)
{
  std::cout << "---- helper amount:" << amount << ",index:" << index << ",useAcount:" << useAcount << ",resAcount:" << resAcount << std::endl;
  if (amount <= 0 || index == coins.size())
  {
    if (amount == 0 && useAcount < resAcount)
    {
      resAcount = useAcount;
    }
    return;
  }

  // 每次都从上一次遍历过的元素位置index开始，继续遍历后面的元素
  for (int i = index; i < coins.size(); i++)
  {
    // 可以选使用
    helper(coins, amount - coins[i], i, useAcount + 1, resAcount);

    // 也可以选不适用该元素
    helper(coins, amount, i + 1, useAcount, resAcount);
  }
}

int coinChange1(vector<int> &coins, int amount)
{
  int resAcount = INT16_MAX;
  helper(coins, amount, 0, 0, resAcount);
  return resAcount == INT16_MAX ? -1 : resAcount;
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // auto res = minCut("cdd"); aab
  // auto res = minCut("leet");
  vector<int> coins = {1, 2, 5};
  int amount = 11;
  auto res = coinChange(coins, amount);
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
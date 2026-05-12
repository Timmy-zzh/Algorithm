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
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要，接着是架构设计
 * -- 每天一个技术点学习，梳理并输出文章出来，一定要写出来分享出去。
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LCR 099. 最小路径和
https://leetcode.cn/problems/0i0mDW/description/

给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：一个机器人每次只能向下或者向右移动一步。

示例 1：
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。

示例 2：
输入：grid = [[1,2,3],[4,5,6]]
输出：12

提示：
m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 100
 */

/**
 * 1、输入一个二维数组的网格grid，网格每个位置是一个节点路径的权重，求从网格左上角到右下角的路径，最小的权重和
 * 2、使用动态规划解法：
 * - 状态转移方程式，使用f(i,j)表示从网格左上角到达网格坐标位置[i,j]时的最小路径和， f(0,0)=grid[0][0]
 * - 最左侧和最上面的路径和，是固定的只有一条路径到达，他们等于 f(0,j) = f(0,j-1)+grid[0][j]
 * - 而中间的位置每个坐标都有两条路径到达，分别是从左侧位置，和从上面位置到达
 * - 所以中间位置的最小路径和等于，两条路径中的最小值加上当前结点的权重: f(i,j) = min(f(i-1,j), f(i,j-1))+ grid[i][j]
 *
 */
int minPathSum(vector<vector<int>> &grid)
{
  int m = grid.size();
  int n = grid[0].size();
  vector<vector<int>> dp(m, vector<int>(n, 0));
  dp[0][0] = grid[0][0];

  for (int i = 1; i < m; i++)
  {
    dp[i][0] = dp[i - 1][0] + grid[i][0];
  }

  for (int j = 1; j < n; j++)
  {
    dp[0][j] = dp[0][j - 1] + grid[0][j];
  }

  for (int i = 1; i < m; i++)
  {
    for (int j = 1; j < n; j++)
    {
      dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
    }
  }
  return dp[m - 1][n - 1];
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // auto res = uniquePaths1(3, 7);
  // auto res = uniquePaths2(3, 7);
  // auto res = uniquePaths(3, 7);
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
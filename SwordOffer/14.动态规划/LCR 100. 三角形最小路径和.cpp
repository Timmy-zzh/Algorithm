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
LCR 100. 三角形最小路径和
https://leetcode.cn/problems/IlPe0q/description/

给定一个三角形 triangle ，找出自顶向下的最小路径和。
每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。

示例 1：
输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
输出：11
解释：如下面简图所示：
   2
  3 4
 6 5 7
4 1 8 3
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

示例 2：
输入：triangle = [[-10]]
输出：-10

提示：
1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-104 <= triangle[i][j] <= 104

进阶：
你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题吗？
 */

/**
 * 优化：使用dp[m]个元素的数组来实现
 * - 存在问题： 之前的数据会被污染，遍历到第i个元素时，dp[i-1]的数据是已经计算过的了
 * - 解决：逆序遍历
 */
int minimumTotal(vector<vector<int>> &triangle)
{
    int m = triangle.size();
    int n = triangle[m - 1].size();
    vector<int> dp(n, 0);
    dp[0] = triangle[0][0];

    for (auto element : dp)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    for (int i = 1; i < m; i++)
    {

        for (int j = i; j >= 0; j--)
        {
            if (j == i)
            {
                dp[j] = dp[j - 1] + triangle[i][i];
            }
            else if (j == 0)
            {
                dp[0] = dp[0] + triangle[i][0];
            }
            else
            {
                dp[j] = min(dp[j - 1], dp[j]) + triangle[i][j];
            }
        }

        for (auto element : dp)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }

    int minRes = INT8_MAX;
    for (int j = 0; j < n; j++)
    {
        minRes = min(minRes, dp[j]);
    }
    return minRes;
}

/**
 * 1、审题：输入一个二维数组，数组中的元素组成一个三角形图案的数字，题目规定从三角形的第一行的数字开始往下走
 * - 且每个数字只能到达他的左右相邻的下一层两个元素，问从第一层开始到最下面一层元素为止的最短路径和多少并返回
 * 2、解题： 动态规划解法
 * - 寻找状态转移方程式，使用f(i,j)表示到达二维数组位置[i,j]时的最短路径和的值
 * - 其中f(0,0) = triangle[0][0]
 * - 第一列的值：f(i,0) = min(f(i-1,0)+trangle[i][0] , f(i-1,j+1)+trangle[i][0] )
 * - 三角形区域其他位置的值为： f(i,j) = min(f(i-1,j)+trangle[i][j] , f(i-1,j+1)+trangle[i][j] )
 * 3、还有一个问题，就是三角形每行最后两个元素的路径之和，要特殊处理，因为上一行最右边元素没有路径下来
 */
int minimumTotal1(vector<vector<int>> &triangle)
{
    int m = triangle.size();
    int n = triangle[0].size();
    vector<vector<int>> dp(m, vector<int>(m, 0));
    dp[0][0] = triangle[0][0];

    // 第二行
    if (m > 1)
    {
        dp[1][0] = dp[0][0] + triangle[1][0];
        dp[1][1] = dp[0][0] + triangle[1][1];
    }
    std::cout << "111" << std::endl;
    for (vector<int> ele : dp)
    {
        for (auto element : ele)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 2; i < m; i++) // i 行
    {
        for (int j = 0; j <= i; j++) // j列
        {
            // 第一列计算
            if (j >= i) // 每行的最后一个
            {
                dp[i][j] = dp[i - 1][i - 1] + triangle[i][j];
            }
            else if (j == 0) // 注意，第一行，只有一条路径
            {
                dp[i][j] = dp[i - 1][j] + triangle[i][j];
            }
            else
            {
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
        }
    }

    std::cout << " last" << std::endl;
    for (vector<int> ele : dp)
    {
        for (auto element : ele)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // 遍历最后一行的路径和，找到最小值
    int minRes = INT8_MAX;
    for (int j = 0; j < m; j++)
    {
        minRes = min(minRes, dp[m - 1][j]);
    }
    return minRes;
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    vector<vector<int>> triangle =
        {{2},
         {3, 4},
         {6, 5, 7},
         {4, 1, 8, 3}};
    auto res = minimumTotal(triangle);

    // vector<vector<int>> triangle =
    //     {{-1},
    //      {3, 2},
    //      {-3, 1, -1}};
    // auto res = minimumTotal(triangle);

    // vector<vector<int>> triangle =
    //     {{-10}};
    // auto res = minimumTotal(triangle);

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
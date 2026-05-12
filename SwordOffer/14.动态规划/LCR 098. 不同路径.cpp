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
LCR 098. 不同路径
https://leetcode.cn/problems/2AoeFn/description/

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
问总共有多少条不同的路径？

示例 1：
输入：m = 3, n = 7
输出：28

示例 2：
输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下

示例 3：
输入：m = 7, n = 3
输出：28

示例 4：
输入：m = 3, n = 3
输出：6

提示：
1 <= m, n <= 100
题目数据保证答案小于等于 2 * 109
 */

/**
 * 动态规划：优化空间效率，使用一维数组来保存数据
 * - 怎么使用一维数组来保存数据呢？ 这个数组的大小是多少？
 * -- 是更长的哪个数据吗？ max（m，n）
 */
int uniquePaths(int m, int n)
{
    vector<int> dp(n, 1);
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[j] += dp[j - 1];
        }
    }
    return dp[n - 1];
}

/**
 * 使用动态规划解法：
 * 状态转移方程式： f(i,j)表示达到网格坐标[i,j]位置时，一共存在的路径和，则他的路径等于左侧位置和上面位置的路径之和
 * - 也就是 f(i,j)=f(i-1,j)+f(i,j-1)
 * - 第一列的位置坐标路径都是1-》f(i,0)=1; 同理第一行位置的路径也全是1：-》f(0,j)=1
 * - 使用二维数据保存网格坐标的路径和
 */
int uniquePaths2(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 1));
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

/**
 * 1、审题：
 * - 输入两个整数m和n，表示网格的行和列，现在要求从网格的左上方位置，移动到网络的右下角位置，
 * - 移动方向一次只能往右，或往下移动一步，问从左上角到右下角移动的路径一共有多少条？
 * 2、解题：
 * - 递归解法，到达网格右下角时的路径一共有两条，分别是左边位置，和上面一格位置。
 * - 而到达左侧和上层位置时，需要的路径又由他的左侧和上层位置的格子形成的路径相加
 * - 直到左侧和上方的位置等于0时，他的路径也只有一条
 * 3、总结：注意网格位置的数字表示，如果从0开始标记，则右下角的位置坐标为(m-1,n-1),
 * - 到达他所在位置的路径和：是其左侧位置(m-1,n-2)和上面位置（m-2,n-1）的路径之和，否则就是从1开始左上角位置了
 */
int uniquePaths1(int m, int n)
{
    if (m <= 1 || n <= 1)
    {
        return 1;
    }

    return uniquePaths1(m - 1, n) + uniquePaths1(m, n - 1);
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    // auto res = uniquePaths1(3, 7);
    // auto res = uniquePaths2(3, 7);
    auto res = uniquePaths(3, 7);
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
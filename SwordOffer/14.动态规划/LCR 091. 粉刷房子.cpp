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
LCR 091. 粉刷房子
https://leetcode.cn/problems/JEj789/description/

假如有一排房子，共 n 个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。每个房子粉刷成不同颜色的花费是以一个 n x 3 的正整数矩阵 costs 来表示的。
例如，costs[0][0] 表示第 0 号房子粉刷成红色的成本花费；costs[1][2] 表示第 1 号房子粉刷成绿色的花费，以此类推。
请计算出粉刷完所有房子最少的花费成本。

示例 1：
输入: costs = [[17,2,17],[16,16,5],[14,3,19]]
输出: 10
解释: 将 0 号房子粉刷成蓝色，1 号房子粉刷成绿色，2 号房子粉刷成蓝色。
     最少花费: 2 + 5 + 3 = 10。

示例 2：
输入: costs = [[7,6,2]]
输出: 2

提示:
costs.length == n
costs[i].length == 3
1 <= n <= 100
1 <= costs[i][j] <= 20
 */

/**
 * 1、审题：输入一个二维数组，二维数组表示有多栋房子，每栋房子可以粉刷成红，绿，蓝三种颜色的粉刷成本，
 * - 要求相邻的房子不能粉刷成同一种颜色，求将所有房子粉刷好最低成本是多少并返回
 * 2、解题：采用动态规划解法
 * - 使用dp[]数组保存每栋房子粉刷不同的颜色所需要的成本，从第一栋房子开始计算，后面的房子根据前面一栋房子粉刷的颜色确定颜色
 * - 一直往后遍历所有的房子，
 * - dp数组也采用二维数组保存房子的粉刷成本，一维数组为房子的个数，二维数组为粉刷颜色红绿蓝的成功保存
 */
int minCost(vector<vector<int>> &costs)
{
    if (costs.size() == 0)
    {
        return 0;
    }
    int n = costs.size();

    // 二维数组赋值为n个vector<int> 其中每个item数组有三个元素
    vector<vector<int>> dp(n, vector<int>(3));

    // 先计算第一栋房子粉刷的成本
    for (int i = 0; i < 3; i++)
    {
        dp[0][i] = costs[0][i];
    }

    /**
     * 从第二栋房子开始，粉刷的颜色成本，要根据前一栋房子的粉刷颜色发生关系
     * 1、如果第二栋房子选择粉刷红色，则前一栋房子选择颜色为（绿，蓝）颜色的最低min成本 + 当前房子的红色成功
     * 2、其他两种颜色粉刷成本是一样的计算思路
     */
    for (int i = 1; i < n; i++)
    {
        // 选择颜色rgb
        for (int j = 0; j < 3; j++)
        {
            if (j == 0) // 当前房子粉刷红色
            {
                dp[i][j] = costs[i][j] + min(dp[i - 1][1], dp[i - 1][2]);
            }
            else if (j == 1)
            {
                dp[i][j] = costs[i][j] + min(dp[i - 1][0], dp[i - 1][2]);
            }
            else if (j == 2)
            {
                dp[i][j] = costs[i][j] + min(dp[i - 1][0], dp[i - 1][1]);
            }
        }
    }

    // 粉刷完最后一栋房子需要的总成功计算出最小值为所求
    return min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2]));
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
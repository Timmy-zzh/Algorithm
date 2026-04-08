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
LCR 088. 使用最小花费爬楼梯
https://leetcode.cn/problems/GzCJIP/description/

数组的每个下标作为一个阶梯，第 i 个阶梯对应着一个非负数的体力花费值 cost[i]（下标从 0 开始）。
每当爬上一个阶梯都要花费对应的体力值，一旦支付了相应的体力值，就可以选择向上爬一个阶梯或者爬两个阶梯。
请找出达到楼层顶部的最低花费。在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯。

示例 1：
输入：cost = [10, 15, 20]
输出：15
解释：最低花费是从 cost[1] 开始，然后走两步即可到阶梯顶，一共花费 15 。

 示例 2：
输入：cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
输出：6
解释：最低花费方式是从 cost[0] 开始，逐个经过那些 1 ，跳过 cost[3] ，一共花费 6 。

提示：
2 <= cost.length <= 1000
0 <= cost[i] <= 999
 */

/**
 * 继续变化
 * - 使用状态转移方程式
 * - dp[i] = min(dp[i-1],dp[i-2]) + cost[i] ，从数组头到尾，计算得到最终的元素数据
 */
int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    vector<int> dp(n, 0);
    dp[0] = cost[0];
    dp[1] = cost[1];

    for (int i = 2; i < n; i++)
    {
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    }
    return min(dp[n - 1], dp[n - 2]);
}

void helper2(vector<int> &cost, int i, vector<int> &dp)
{
    if (i < 2)
    {
        dp[i] = cost[i];
    }
    else if (dp[i] == 0)
    {
        // 继续网底层递归，递归万后，再计算最小值，从下到上顺序
        helper2(cost, i - 1, dp);
        helper2(cost, i - 2, dp);
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    }
}

/**
 * 第一种方法使用的方程式进行叠加计算时，会存在重复计算的问题
 * 使用一个数组保存他之前已经计算过的f(n)的值，这样可以避免重复计算
 */
int minCostClimbingStairs2(vector<int> &cost)
{
    int n = cost.size();
    // 使用一个数组保存
    vector<int> dp(n, 0);
    helper2(cost, n - 1, dp);
    helper2(cost, n - 2, dp);

    for (auto ele : dp)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    return min(dp[n - 1], dp[n - 2]);
}

/**
 * 1、审题：输入一个数组，数组个数表示一共存在的台阶，每个元素值表示从这个台阶出发需要消耗的体力值
 * - 每次消耗体力值，从当前台阶出发可以往上行走1级，也可以往上走2级
 * - 最后求从第1级台阶，往上走到楼梯最低端消耗的最少体力值是多少
 * 2、解题：动态规划解法
 * - 找到规律，到达楼梯最顶部n，可以拆解为从n-1步阶梯往上，或者从n-2级阶梯往上再走一步，
 * - 其他步的解题也可以按照这种思路，可以得出方程式，假设使用f(n)表示到达第n级台阶需要消耗的体力值
 * - 那等于 f(n-1)+cost[n-1] 或者 f(n-2)+cost[n-2]; 然后从中间选择一个最小值
 * - 当n等于1，或2 时f(n) = cost[n]
 * 3、有个问题没搞明白，从第0步开始往上需要消耗多少体力值呢？
 * - 默认用户站在第一个，或第二个阶梯上，本身已经消耗当前的体力值到达了当前位置，然后继续从该位置继续往后走
 */

int helper1(vector<int> &cost, int i)
{
    if (i < 2)
    {
        return cost[i];
    }
    return min(helper1(cost, i - 2), helper1(cost, i - 1)) + cost[i];
}

int minCostClimbingStairs1(vector<int> &cost)
{
    int len = cost.size();
    return min(helper1(cost, len - 1), helper1(cost, len - 2));
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
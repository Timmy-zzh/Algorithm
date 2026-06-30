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
LCR 104. 组合总和 Ⅳ
https://leetcode.cn/problems/D0F0SV/description/

给定一个由 不同 正整数组成的数组 nums ，和一个目标整数 target 。请从 nums 中找出并返回总和为 target 的元素组合的个数。
数组中的数字可以在一次排列中出现任意次，但是顺序不同的序列被视作不同的组合。
题目数据保证答案符合 32 位整数范围。

示例 1：
输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。

示例 2：
输入：nums = [9], target = 3
输出：0

提示：
1 <= nums.length <= 200
1 <= nums[i] <= 1000
nums 中的所有元素 互不相同
1 <= target <= 1000

进阶：如果给定的数组中含有负数会发生什么？问题会产生何种变化？如果允许负数出现，需要向题目中添加哪些限制条件？
 */

/**
 * 1、审题：
 * - 输入一个正整数数组，和一个目标值target，要求从数组中取出若干个元素组成子数组，要求这些子数组的和等于目标值target
 * - 数组中每个元素可以重复多次使用，求目标子数组的总个数组并返回，
 * - 要求子数组中元素要有顺，相同的元素，组成不同的顺序那就是不同的组合情况
 * 2、解题： 动态规划解法 - 状态转移方程式
 * - 使用以为数组dp[i] 表示子数组和为i的所有子数组的组合个数，其中dp[0]=1; 表示子数组和为0的组合只有一种情况，那就是什么元素都不选
 * - dp[i]的值，可以转换为dp[i-nums[0]]与dp[i]的关系 ，也就是和为i-nums[0]的子数组个数，添加了1个nums[0]的元素后的值，也就还dp[i]= dp[i]+dp[i-nums[0]]
 * - 也可以转换为，添加1个nums[1]后元素的值，也就是 dp[i]= dp[i]+dp[i-nums[1]] ，在和为i-nums[1]的子数组个数的基础上加上一个nums[1]的元素后的，子数组的和的个数
 * - 那dp[i] 也可以添加第n个元素发生关系，也就在和为i-nums[n-1]的基础上添加一个nums[n-1]的元素后的，子数组的和的个数，
 * - 而dp[i] 的最终值，等于dp[i-nums[j]] (0<= j <n)的子数组元素的所有个数的累加和
 */
int combinationSum4(vector<int> &nums, int target)
{
    vector<unsigned int> dp(target + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= target; i++)
    {
        for (auto num : nums)
        {
            if (i >= num)
            {
                dp[i] += dp[i - num];
            }
        }
    }
    return dp[target];
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    // auto res = minCut("cdd"); aab
    // auto res = minCut("leet");
    vector<int> coins = {1, 2, 3};
    int amount = 4;
    auto res = combinationSum4(coins, amount);
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
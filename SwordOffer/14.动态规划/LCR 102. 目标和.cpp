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
LCR 102. 目标和
https://leetcode.cn/problems/YaVDxD/description/

给定一个正整数数组 nums 和一个整数 target 。
向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

示例 1：
输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

示例 2：
输入：nums = [1], target = 1
输出：1

提示：
1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000
 */

/**
 * 动态规划解法：
 * - 确定状态转移方程式
 * - 使用i表示数组nums包含的元素个数，j表示i个元素形成的累加和，f(i,j)值表示i个元素累加和等于j的组合的个数
 * - 则 f(i,j) = f(i-1,j-nums[i]) + f(i-1,j+nums[i])
 * - f(0,0)=1
 * - f(0,j) 0个元素要求累加和等于j（j>0)没有满足条件，结果全为0 (第一行所有元素)
 * - f(i,0) 第一列，他的值= f(i-1,0-nums[i]) + f(i-1,0+nums[i]) 且列要求>=0
 */
int findTargetSumWays(vector<int> &nums, int target)
{
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    dp[0][0] = 1;

    for (vector<int> ele : dp)
    {
        for (auto element : ele)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= target; j++)
        {
            int idx1 = j + nums[i - 1];
            if (idx1 >= 0 && idx1 <= target)
            {
                dp[i][j] += dp[i - 1][idx1];
            }

            int idx2 = j - nums[i - 1];
            if (idx2 >= 0 && idx2 <= target)
            {
                dp[i][j] += dp[i - 1][idx2];
            }

            std::cout << "---i:" << i << " ,j:" << j << ",nums[i]:" << nums[i - 1] << std::endl;
            for (vector<int> ele : dp)
            {
                for (auto element : ele)
                {
                    std::cout << element << ",";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
    return dp[n][target];
}

/**
 * 1、审题：
 * - 输入一个整数数组和一个target目标值，要求在数组元素的前面选择正/负数符号,使得最后的元素累加和等于目标值
 * - 因为每个元素都有两种符号选择，问一共有多少种组合序列，并返回
 * 2、解题：
 * - 回溯法： 每个元素都有两种选择，到最后的累加和等于目标值说明这个组合命中目标，累加个数加一
 */

void helper(vector<int> &nums, int target, int i, int &resNum)
{
    if (i == nums.size())
    {
        if (target == 0)
        {
            resNum = resNum + 1;
        }
        return;
    }

    // 当前元素的两种选择
    helper(nums, target + nums[i], i + 1, resNum);

    helper(nums, target - nums[i], i + 1, resNum);
}

int findTargetSumWays1(vector<int> &nums, int target)
{
    int resNum = 0;
    helper(nums, target, 0, resNum);
    return resNum;
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    // auto res = minCut("cdd"); aab
    // auto res = minCut("leet");
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    auto res = findTargetSumWays(nums, target);
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
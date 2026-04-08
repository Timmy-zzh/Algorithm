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
LCR 090. 打家劫舍 II
https://leetcode.cn/problems/PzWKhm/description/

一个专业的小偷，计划偷窃一个环形街道上沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，
这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
给定一个代表每个房屋存放金额的非负整数数组 nums ，请计算 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。

示例 1：
输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。

示例 2：
输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。

示例 3：
输入：nums = [0]
输出：0

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 1000
 */

/**
 * 1、审题：
 * - 输入一个数组，表示一个环形房屋内每个房子的金额，现在有小偷想偷盗房间内的财物
 * - 偷盗时不能同时偷盗相邻房间，否则会触发警报，问小偷能够偷盗的最大财物金额，并返回
 * 2、解题：
 * - 和之前打家劫舍的解题思路一样，不够这里有个限制，不能同时偷盗首位两座房屋的财物，
 * - 可以将当前问题拆分成两个：一个是偷盗第一个房屋，就不偷盗最后的房屋。或者偷盗最后一个房屋，不偷盗第一个访问，这样来计算两种情况下偷盗的最大值
 * - 采用dp数组记录偷盗了第i个房屋时，偷盗的最大金额，他们的状态转移方程式为
 * - dp[i] = max(dp[i-1], dp[i-2]+cost[i])
 */

int helper(vector<int> &nums, int start, int end)
{
    vector<int> dp(end + 1, 0);

    // 先将前面的两个数字填充完整
    dp[start] = nums[start];
    dp[start + 1] = max(nums[start], nums[start + 1]);
    for (int i = start + 2; i <= end; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    // 遍历1维数组
    std::cout << "start:" << start << " ,end:" << end << std::endl;
    for (auto ele : dp)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    return dp[end];
}

int rob(vector<int> &nums)
{
    if (nums.size() == 0)
    {
        return 0;
    }
    if (nums.size() == 1)
    {
        return nums[0];
    }

    if (nums.size() == 2)
    {
        return max(nums[0], nums[1]);
    }

    int n = nums.size();
    int res1 = helper(nums, 0, n - 2);
    int res2 = helper(nums, 1, n - 1);
    return max(res1, res2);
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
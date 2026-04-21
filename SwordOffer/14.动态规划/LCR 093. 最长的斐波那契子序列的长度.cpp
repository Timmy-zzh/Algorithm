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
LCR 093. 最长的斐波那契子序列的长度
https://leetcode.cn/problems/Q91FMA/description/

如果序列 X_1, X_2, ..., X_n 满足下列条件，就说它是 斐波那契式 的：
n >= 3
对于所有 i + 2 <= n，都有 X_i + X_{i+1} = X_{i+2}
给定一个严格递增的正整数数组形成序列 arr ，找到 arr 中最长的斐波那契式的子序列的长度。如果一个不存在，返回  0 。
（回想一下，子序列是从原序列  arr 中派生出来的，它从 arr 中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， [3, 5, 8] 是 [3, 4, 5, 6, 7, 8] 的一个子序列）

示例 1：
输入: arr = [1,2,3,4,5,6,7,8]
输出: 5
解释: 最长的斐波那契式子序列为 [1,2,3,5,8] 。

示例 2：
输入: arr = [1,3,7,11,12,14,18]
输出: 3
解释: 最长的斐波那契式子序列有 [1,11,12]、[3,11,14] 以及 [7,11,18] 。

提示：
3 <= arr.length <= 1000
1 <= arr[i] < arr[i + 1] <= 10^9
 */

/**
 * 回溯法会检索所有的分支情况，这个题目只需要最长的斐波拉楔子数组场景，算法复杂度高，改用动态规划解法
 * 动态规划:
 * - 求状态转移方程式，假设存在符合斐波拉楔情况的子数组元素，他们一定满足条件 arr[i] = arr[j] + arr[k],且 0<= k < j < i
 * - 使用方程式f(i,j)表示从数组范围[j,i]存在的符合斐波拉楔情况的子数组长度，
 * - 则往前推进一步也可能存在 f(j,k)的斐波拉楔子数组情况，他们的关系为 f(i,j) = f(j,k) + 1;
 * - 使用两层for循环，外层for循环从下标1开始，获取数组arr[i]元素
 * - 内层for循环，从0到i，表示元素arr[j]
 * - 判断在原始数组中是否存在arr[k]; 使得arr[k]+arr[j]=arr[i]; 存在的话则有dp[i][j]=dp[j][k]+1; 求出k的下标位置
 * - 如果没有则dp[i][j]=2
 */
int lenLongestFibSubseq(vector<int> &arr)
{
    // 保存元素和对应的下标位置
    int n = arr.size();
    map<int, int> numMap;
    for (int i = 0; i < n; i++)
    {
        numMap[arr[i]] = i;
    }

    int maxRes = 2;
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // 判断 arr[k] = arr[i]-arr[j] 是否存在
            int arrK = arr[i] - arr[j];
            if (numMap.find(arrK) != numMap.end() && numMap[arrK] < j) // 存在
            {
                int k = numMap[arrK];
                dp[i][j] = dp[j][k] + 1;
            }
            else // 不存在，则dp[i][j]=2
            {
                dp[i][j] = 2;
            }
            maxRes = max(maxRes, dp[i][j]);
        }
    }
    return maxRes > 2 ? maxRes : 0;
}

/**
 * 1、审题：输入一个整数数组，数组元素为递增的整数，要求从数组中找出一个子数组，子数组元素为斐波拉楔序列，要求符合要求的最长子数组长度并返回
 * 2、解题：
 * - 回溯法：要求符合斐波拉楔条件的子数组，每个元素都有两种选择情况，可以使用回溯法求出所有符合要求的子数组，然后寻找到最长长度的子数组
 * 3、总结： item.size() 数组类型是typedef size_t	size_type;需要转换成int类型参数，再进行max函数的调用
 */
int maxRes = 2;

void helper1(vector<int> &arr, vector<int> &item, int i)
{
    if (i == arr.size())
    {
        maxRes = max(maxRes, static_cast<int>(item.size()));
        return;
    }

    // 遍历到数组元素第i位置的元素了，现在有两种选择方式

    // 1、如果item个数小于2，arr[i]元素可以放数组中，也可以不放
    if (item.size() < 2)
    {
        helper1(arr, item, i + 1);

        item.push_back(arr[i]);
        helper1(arr, item, i + 1);
        item.pop_back();
    }
    else
    {
        // 超过两个了，可以选择不放入其中，但如果要放入其中，则要求组成斐波拉楔条件
        helper1(arr, item, i + 1);

        //
        int n = item.size();
        if (arr[i] == (item[n - 1] + item[n - 2]))
        {
            item.push_back(arr[i]);
            helper1(arr, item, i + 1);
            item.pop_back();
        }
    }
}

int lenLongestFibSubseq1(vector<int> &arr)
{
    vector<int> item;
    helper1(arr, item, 0);
    return maxRes == 2 ? 0 : maxRes;
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
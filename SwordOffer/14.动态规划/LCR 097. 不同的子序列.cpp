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
LCR 097. 不同的子序列
https://leetcode.cn/problems/21dk04/description/

给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。
字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。
（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）
题目数据保证答案符合 32 位带符号整数范围。

示例 1：
输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
rabbbit
rabbbit
rabbbit

示例 2：
输入：s = "babgbag", t = "bag"
输出：5
解释：
如下图所示, 有 5 种可以从 s 中得到 "bag" 的方案。
babgbag
babgbag
babgbag
babgbag
babgbag

提示：
0 <= s.length, t.length <= 1000
s 和 t 由英文字母组成
 */

/**
 * 使用动态规划解法：
 * - 寻找状态转移方程式
 * - 要查找字符串s的子序列，与字符串t相等的个数，涉及到两个对象，使用f(i,j)来表示字符串s[0,i],字符串t[0,j]时的位置，存在相等子序列的个数
 * - 当s[i] == t[j] 时，f(i,j) = max(f(i-1,j)+1 , f(i,j));, 表示
 * - 当s[i] != t[j] 时，f(i,j) = 0;
 */
int numDistinct(string s, string t)
{
    if (s.length() < t.length())
    {
        return 0;
    }
    if (s.length() == 0 && t.length() == 0)
    {
        return 1;
    }
    if (s.length() == 0 || t.length() == 0)
    {
        return 0;
    }

    int sLen = s.length();
    int tLen = t.length();
    vector<vector<unsigned long long>> dp(sLen + 1, vector<unsigned long long>(tLen + 1, 0));
    dp[0][0] = 1;

    // for (vector<long> ele : dp)
    // {
    //   for (auto element : ele)
    //   {
    //     std::cout << element << ",";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << " --------------- " << std::endl;

    for (int i = 0; i < sLen; i++)
    {
        dp[i + 1][0] = 1;
        for (int j = 0; j < tLen && j <= i; j++) // j得长度要去小于等于i，否则太长没有满足条件的子序列
        {
            if (s[i] == t[j]) // 遇到一样的字符
            {
                dp[i + 1][j + 1] = dp[i][j] + dp[i][j + 1];
            }
            else // 遇到不一样的字符，和更短的字符串一样的子序列个数
            {
                dp[i + 1][j + 1] = dp[i][j + 1];
            }
        }
    }
    // for (vector<long> ele : dp)
    // {
    //   for (auto element : ele)
    //   {
    //     std::cout << element << ",";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;
    return dp[sLen][tLen];
}

/**
 * 1、审题： 输入两个字符串s和t，求字符串s的子序列，有多少个和字符串t相同
 * 2、解题：
 * - 字符串子序列，是将字符串中的字符删除0个或多个，不改变原先的排序，最终得到的字符串
 * - 1）使用回溯法解题，遍历两个字符串
 * -- 面对不相等的字符，长字符串进行跳过
 * -- 当面对相等的字符时，长字符串可以选择跳过，或保留，如果保留则短字符串s同样消耗一个字符
 * - 最终短字符串t中字符全部消耗完毕
 */
void helper(string &s, string &t, int lPos, int sPos, int &resCount)
{
    if (sPos == t.length())
    {
        resCount++;
        return;
    }

    if (lPos >= s.length())
    {
        return;
    }

    if (s[lPos] != t[sPos]) // 遍历到不相等的字符，长字符串继续往后遍历
    {
        helper(s, t, lPos + 1, sPos, resCount);
    }
    else
    { // 相等，面临两种情况
        // 直接跳过
        helper(s, t, lPos + 1, sPos, resCount);

        // 或者一同消耗
        helper(s, t, lPos + 1, sPos + 1, resCount);
    }
}

int numDistinct1(string s, string t)
{
    if (s.length() < t.length())
    {
        return 0;
    }
    int resCount = 0;
    helper(s, t, 0, 0, resCount);
    return resCount;
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    auto res = numDistinct("rabbbit", "rabbit");
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
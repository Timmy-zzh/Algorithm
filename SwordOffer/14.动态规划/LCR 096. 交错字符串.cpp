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
LCR 096. 交错字符串
https://leetcode.cn/problems/IY6buf/description/

给定三个字符串 s1、s2、s3，请判断 s3 能不能由 s1 和 s2 交织（交错） 组成。
两个字符串 s 和 t 交织 的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：
s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
交织 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
提示：a + b 意味着字符串 a 和 b 连接。

示例 1：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出：true

示例 2：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出：false
示例 3：

输入：s1 = "", s2 = "", s3 = ""
输出：true

提示：
0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1、s2、和 s3 都由小写英文字母组成
 */

/**
 * 动态规划解法：其实和回溯法的思路是一样的，只是思路的应用不同，回溯法是遍历所有的情况，状态转移是根据之前状态结果来推导后面的结果
 * - 状态转移方程式： 使用f(i,j)表示 字符串s1在位置i，s2在位置j，s3在位置(i+j) 时，是否存在符合条件的交错字符串
 * - 如果s3[i+j]==s1[i]相同, 则f(i,j)的值为 = f(i-1,j)
 * --   s3[i+j]==s2[j]相同, 则f(i,j)的值为 = f(i,j-1)
 * == 都相同 s3[i+j]==s1[i]，&& s3[i+j]==s2[j] ，则f(i,j) = f(i-1,j) ||  f(i,j-1)
 * == 如果s3[i+j]！=s1[i]，&& s3[i+j]!=s2[j] ，则则f(i,j) = false
 */
bool isInterleave(string s1, string s2, string s3)
{
    int len1 = s1.length();
    int len2 = s2.length();
    int len3 = s3.length();
    if (len3 != len1 + len2)
    {
        return false;
    }

    vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
    dp[0][0] = true;

    // 先把第一行，和第一列的dp数据求出来
    for (int i = 0; i < len1; i++)
    {
        if (s1[i] == s3[i])
        {
            dp[i + 1][0] = dp[i][0];
        }
    }

    for (int j = 0; j < len2; j++)
    {
        if (s2[j] == s3[j])
        {
            dp[0][j + 1] = dp[0][j];
        }
    }

    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            char ch1 = s1[i];
            char ch2 = s2[j];
            char ch3 = s3[i + j + 1]; // 根据i,j 求长字符串的遍历位置，注意

            if (ch3 == ch1 && ch3 == ch2)
            {
                dp[i + 1][j + 1] = dp[i + 1][j] || dp[i][j + 1];
            }
            else if (ch3 == ch1 && ch3 != ch2)
            {
                dp[i + 1][j + 1] = dp[i][j + 1];
            }
            else if (ch3 != ch1 && ch3 == ch2)
            {
                dp[i + 1][j + 1] = dp[i + 1][j];
            }
            else
            {
                dp[i + 1][j + 1] = false;
            }
        }
    }

    for (vector<bool> ele : dp)
    {
        for (auto element : ele)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return dp[len1][len2];
}

/**
 * 1、审题：
 * - 输入两个短字符串s1，s2，和一个长字符串s3，判断长字符串s3是否可以由s1和s2组成
 * 2、解题：
 * - 回溯法解题
 * - 不断从s1或s2字符串中取去一个字符，判断是否和当前s3中取出的字符是否相等，其中只要有一个相同的则继续往前递归遍历，
 * - 如果两个都不同，则直接返回false，中断
 */
bool helper(string &s1, string &s2, string &s3, int n1, int n2, int n3)
{
    std::cout << " --- n1:" << n1 << " ,n2:" << n2 << " ,n3:" << n3 << std::endl;

    if (n1 > s1.length() || n2 > s2.length() || n3 > s3.length())
    {
        return false;
    }

    if (n1 == s1.length() && n2 == s2.length() && n3 == s3.length())
    {
        return true;
    }

    int res1 = false;
    int res2 = false;
    if (n1 < s1.length() && s1[n1] == s3[n3])
    {
        res1 = helper(s1, s2, s3, n1 + 1, n2, n3 + 1);
    }

    if (n2 < s2.length() && s2[n2] == s3[n3])
    {
        res2 = helper(s1, s2, s3, n1, n2 + 1, n3 + 1);
    }

    return res1 || res2;
}

bool isInterleave1(string s1, string s2, string s3)
{
    return helper(s1, s2, s3, 0, 0, 0);
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    auto res = isInterleave("aabcc", "dbbca", "aadbbcbcac");
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
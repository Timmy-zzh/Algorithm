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
LCR 092. 将字符串翻转到单调递增
https://leetcode.cn/problems/cyJERH/description/

如果一个由 '0' 和 '1' 组成的字符串，是以一些 '0'（可能没有 '0'）后面跟着一些 '1'（也可能没有 '1'）的形式组成的，那么该字符串是 单调递增 的。
我们给出一个由字符 '0' 和 '1' 组成的字符串 s，我们可以将任何 '0' 翻转为 '1' 或者将 '1' 翻转为 '0'。
返回使 s 单调递增 的最小翻转次数。

示例 1：
输入：s = "00110"
输出：1
解释：我们翻转最后一位得到 00111.

示例 2：
输入：s = "010110"
输出：2
解释：我们翻转得到 011111，或者是 000111。

示例 3：
输入：s = "00011000"
输出：2
解释：我们翻转得到 00000000。

提示：
1 <= s.length <= 20000
s 中只包含字符 '0' 和 '1'
 */

/**
 * 使用动态规划解法：
 * - 求状态转移方程式，既然每个字符都有两种翻转情况，那就设置两个函数f(i)与 g(i)
 * - f(i)表示所有的字符都是0，所得到的翻转的次数，具体情况：
 * -- s[i]='0', 则不需要翻转 f(i) = f(i-1);   f(0)=0
 * -- s[i]='1', 则需要翻转 f(i)= f(i-1) +1; f(0)=1
 * - g(i) 表示最后翻转后的字符为'1',则：
 * -- s[i]='0',则需要翻转，且前面的i-1位置的翻转次数取最小值 g(i) = min(f(i-1),g(i-1)) +1;   g(0)=1
 * -- s[i]='1', 不需要翻转，g(i) = min(f(i-1),g(i-1)) ; g(0)=1
 * - 使用dp二维数组来表示f(i);与 g(i)的情况
 */
int minFlipsMonoIncr(string s)
{
    int n = s.length();
    vector<vector<int>> dp(2, vector<int>(n));

    if (s[0] == '0')
    {
        dp[0][0] = 0;
        dp[1][0] = 1;
    }
    else
    {
        dp[0][0] = 1;
        dp[1][0] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        if (s[i] == '0')
        {
            dp[0][i] = dp[0][i - 1];
            dp[1][i] = min(dp[0][i - 1], dp[1][i - 1]) + 1;
        }
        else
        {
            dp[0][i] = dp[0][i - 1] + 1;
            dp[1][i] = min(dp[0][i - 1], dp[1][i - 1]);
        }
    }

    return min(dp[0][n - 1], dp[1][n - 1]);
}

/**
 * 1、审题：输入一个字符串，字符串内容由0和1字符所组成，现在要求对字符串中单个字符进行翻转，要求反转后所有的字符0在前面，字符1在后面
 * - 也就是字符单调递增字符串，求达成单调递增字符串需要翻转的最低次数
 * 2、解题：
 * - 回溯法实现思路：
 * -- 每个字符处理时都有两种操作方式，一种是翻转或者不翻转，并记录翻转的次数，到最后一个字符时结束递归，每次翻转后要求操作还原
 * -- 判断最后处理的字符串是否是单调递增，是的话计算最低翻转次数，并求出最小值
 */
int minRes = INT32_MAX;

/**
 * 判断字符串是否是单调递增
 * 字符0全部在前面
 * - 碰到0，前面要求是0，否则false
 * - 碰到1，后面要求是1，否则false
 */
bool isOk(string &s)
{
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] == '0')
        {
            if (s[i - 1] != '0')
            {
                return false;
            }
        }
        else
        {
            if (i == s.length() - 1) // 最后一个字符是1
            {
                return true;
            }
            if (s[i + 1] != '1')
            {
                return false;
            }
        }
    }
    return true;
}

void helper1(string &s, int i, int count)
{
    if (i == s.length())
    {
        if (isOk(s))
        {
            minRes = min(minRes, count);
        }
        return;
    }
    // 当前字符不翻转
    helper1(s, i + 1, count);

    // 翻转
    if (s[i] == '0')
    {
        // 翻转成1
        s[i] = '1';
        helper1(s, i + 1, count + 1);
        s[i] = '0';
    }
    else
    {
        // 翻转成1
        s[i] = '0';
        helper1(s, i + 1, count + 1);
        s[i] = '1';
    }
}

int minFlipsMonoIncr1(string s)
{
    helper1(s, 0, 0);
    return minRes;
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
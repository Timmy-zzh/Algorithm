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
LCR 095. 最长公共子序列
https://leetcode.cn/problems/qJnOS7/description/

给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

示例 1：
输入：text1 = "abcde", text2 = "ace"
输出：3
解释：最长公共子序列是 "ace" ，它的长度为 3 。

示例 2：
输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc" ，它的长度为 3 。

示例 3：
输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0 。

提示：
1 <= text1.length, text2.length <= 1000
text1 和 text2 仅由小写英文字符组成。
 */

/**
 * 1、审题：
 * - 输入两个字符串，要求两个字符串的最长公共子序列，并返回他的长度
 * 2、解题：
 * - 问题1：两个字符串如何求他的最长公共子序列呢？
 * 动态规划解法：
 * - 使用二维数据表示两个字符串的最长公共子序列的长度，f(i,j) 表示字符串1-S1[0,i]，和字符串2-S2[0,j]的最长公共子序列的长度
 * - 在遍历过程中如果s[i]==s[j],则 f(i,j)=f(i-1,j-1)+1; 这是字符相等的情况
 * - 如果字符不相等，则f(i,j)=max(f(i-1,j), f(i,j-1));
 * - 默认dp[i][j]最边上的值全为0，当f(0,0)时f(-1,-1)超过限制了，所以数据改为往前移动一位从f(1,1)开始
 */
int longestCommonSubsequence(string text1, string text2)
{
  int len1 = text1.length();
  int len2 = text2.length();

  vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
  for (size_t i = 0; i < len1; i++)
  {
    for (size_t j = 0; j < len2; j++)
    {
      if (text1[i] == text2[j])
      {
        dp[i + 1][j + 1] = dp[i][j] + 1;
      }
      else
      {
        dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
      }
    }
  }
  return dp[len1][len2];
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // auto res = minCut("cdd"); aab
  // auto res = minCut("leet");
  // auto res = minCut("aab");
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
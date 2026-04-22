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
LCR 094. 分割回文串 II
https://leetcode.cn/problems/omKAoA/description/

给定一个字符串 s，请将 s 分割成一些子串，使每个子串都是回文串。
返回符合要求的 最少分割次数 。

示例 1：
输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。

示例 2：
输入：s = "a"
输出：0

示例 3：
输入：s = "ab"
输出：1

提示：
1 <= s.length <= 2000
s 仅由小写英文字母组成
 */

/**
 * 动态规划解法：
 * - 求状态转移方程式：
 * - 先使用二维数组isPal[i][j] 表示从字符串位置i到j的位置的[i,j]子字符串，是否是回文串标记bool
 * -- 这个二维数组的值，可以通过两层for循环求解得到，
 * - 再使用f(i)表示子字符串S[0,i]位置所需要分割的次数，如果S[0,i]的子字符串是回文串，则不需要进行分割，f(i)的结果为0；
 * - 如果S[0,i]这个子字符串不是回文串，则需要分割，分割的位置假设为j，存在关系为 0 < j < i，且要求分割后的子字符串S[j,i]是回文串，
 * -- 则f(i)的值等于 f(j)的值加1，
 * - 而j的位置可能存在多个，我们要取最小f(j)的值
 */
int minCut(string s)
{
  int count = s.length();
  vector<vector<bool>> isPal(count, vector<bool>(count, false));
  for (int i = 0; i < count; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      char chI = s[i];
      char chJ = s[j];
      // 求子字符串S[j,i]是否是回文串
      if (chI == chJ && (i <= j + 1 || isPal[j + 1][i - 1]))
      {
        // 中间位置的子字符串为回文串，再延伸到头尾的字符也相等，则该子字符串也是回文串，
        isPal[j][i] = true;
      }
    }
  }

  // 使用dp[]数组，表示从子字符串S[0,i]的分割次数
  vector<int> dp(count, 0);
  for (int i = 0; i < count; i++)
  {
    if (isPal[0][i])
    {
      dp[i] = 0;
    }
    else
    {
      // 要求分割后的子字符串S[j,i]是回文串，取最小f(j)的值
      dp[i] = i;
      for (int j = 1; j <= i; j++)
      {
        if (isPal[j][i])
        {
          dp[i] = min(dp[i], dp[j - 1] + 1);
        }
      }
    }
  }
  return dp[count - 1];
}

/**
 * 1、审题：
 * - 输入一个字符串，对字符串中的字符进行分割，要求分割后的子字符串都是回文串，求最少分割的次数并返回
 * 2、解题：
 * 回溯法
 * - 每个字符都有两种选择，分割或者不分割，将所有分割的情况放到数组中，并最终判断是否所有的子字符串是否都是回文串，是的话求出最小的分割次数
 * 3、总结：使用回溯法记得每次往item中添加元素后，使用万要删除该元素
 * - 数据裁剪
 */
int minRes = INT8_MAX;

/**
 * 判断字符串是否是回文串
 * - 双指针解法，从头尾两个方向的字符不断判断
 * - 遇到相同的，则从两头开始网内收缩，否则就不是回文串
 */
bool isPalindrome(string &s)
{
  int start = 0;
  int end = s.length() - 1;
  while (start < end)
  {
    if (s[start] != s[end])
    {
      return false;
    }
    start++;
    end--;
  }
  return true;
}

bool isAllPalindrome(vector<string> &item)
{
  std::cout << " isAllPalindrome  --------- " << std::endl;
  // 遍历1维数组
  for (auto ele : item)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;

  for (int i = 0; i < item.size(); i++)
  {
    if (!isPalindrome(item[i]))
    {
      return false;
    }
  }
  return true;
}

/**
 * @param start ,上一次切割字符的位置
 * @param end 当前遍历到的位置
 */
void helper(string &s, vector<string> &item, int start, int end)
{

  std::cout << " --- start:" << start << " ,end:" << end << std::endl;
  // 遍历1维数组
  for (auto ele : item)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;

  if (start >= s.length())
  {
    return;
  }

  if (end == s.length())
  {
    // 结束，将最后一个字符存入数组中
    if (item.size() == 0) // 一刀不切的
    {
      return;
    }
    else if (start != end)
    {
      item.push_back(s.substr(start, end - start));
      if (isAllPalindrome(item))
      {
        std::cout << " === isAllPalindrome true" << std::endl;
        minRes = min(minRes, static_cast<int>(item.size() - 1));
      }
      item.pop_back();
    }
    return;
  }

  // 选择不分割
  helper(s, item, start, end + 1);

  // 选择分割
  std::cout << " ------ start:" << start << " ,end:" << end << std::endl;
  string itemStr = s.substr(start, end - start);
  std::cout << " itemStr:" << itemStr << std::endl;
  if (isPalindrome(itemStr))
  {
    item.push_back(itemStr);
    helper(s, item, end, end + 1);
    item.pop_back();
  }
}

int minCut1(string s)
{
  if (isPalindrome(s))
  {
    return 0;
  }
  vector<string> item;
  helper(s, item, 0, 1);
  return minRes;
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // auto res = minCut("cdd"); aab
  // auto res = minCut("leet");
  auto res = minCut("aab");
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
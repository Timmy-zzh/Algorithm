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
 * 1、审题：
 * - 输入一个字符串，对字符串中的字符进行分割，要求分割后的子字符串都是回文串，求最少分割的次数并返回
 * 2、解题：
 * 回溯法
 * - 每个字符都有两种选择，分割或者不分割，将所有分割的情况放到数组中，并最终判断是否所有的子字符串是否都是回文串，是的话求出最小的分割次数
 *
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
void helper(string &s, vector<string> &item, int start, int end, int count)
{
  if (start >= s.length())
  {
    return;
  }

  if (end == s.length())
  {
    // 结束，将最后一个字符存入数组中
    if (start != end)
    {
      item.push_back(s.substr(start, end - start));
    }
    if (isAllPalindrome(item))
    {
      minRes = min(minRes, count);
    }
    return;
  }

  // 选择不分割
  helper(s, item, start, end + 1, count);

  // 选择分割
  item.push_back(s.substr(start, end - start));
  helper(s, item, end, end + 1, count + 1);
  item.pop_back();
}

int minCut(string s)
{
  vector<string> item;
  helper(s, item, 0, 1, 0);
  return minRes;
}

int main()
{
  std::cout << "《剑指》" << std::endl;

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
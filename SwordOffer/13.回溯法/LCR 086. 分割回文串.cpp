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
LCR 086. 分割回文串
https://leetcode.cn/problems/M99OJA/description/

给定一个字符串 s ，请将 s 分割成一些子串，使每个子串都是 回文串 ，返回 s 所有可能的分割方案。
回文串 是正着读和反着读都一样的字符串。

示例 1：
输入：s = "google"
输出：[["g","o","o","g","l","e"],["g","oo","g","l","e"],["goog","l","e"]]

示例 2：
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]

示例 3：
输入：s = "a"
输出：[["a"]]

提示：
1 <= s.length <= 16
s 仅由小写英文字母组成
 */

bool isPalind(string s, int start, int end)
{
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

void helper(string s, int start, vector<string> &item, vector<vector<string>> &res)
{
  if (start == s.length())
  {
    res.push_back(item);
    return;
  }
  for (int i = start; i < s.length(); i++)
  {
    // 判断当前子字符串是否是回文串 [start,i]，是的话添加到item中，并继续进行下一次子字符串的遍历查询
    if (isPalind(s, start, i))
    {
      item.push_back(s.substr(start, i - start + 1));
      helper(s, i + 1, item, res);
      item.pop_back();
    }
  }
}

/**
 * 1、审题：输入一个字符串，要求将字符串进行分割，分割后的子字符串，能够是回文串，并返回所有分割的集合
 * 2、解题：回溯法，递归实现，从左到右不断对原先的字符串进行分割，每次分割后判断子字符串是否是回文串，
 * - 是的话添加到集合中，并最终保存到res集合中取
 */
vector<vector<string>> partition(string s)
{
  vector<vector<string>> res;
  vector<string> item;
  helper(s, 0, item, res);
  return res;
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
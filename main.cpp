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
#include <unordered_set>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。写就是思考
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LeetCode 318. 最大单词长度乘积
https://leetcode.cn/problems/maximum-product-of-word-lengths/description/

给你一个字符串数组 words ，找出并返回 length(words[i]) * length(words[j]) 的最大值，并且这两个单词不含有公共字母。如果不存在这样的两个单词，返回 0 。

示例 1：
输入：words = ["abcw","baz","foo","bar","xtfn","abcdef"]
输出：16
解释：这两个单词为 "abcw", "xtfn"。

示例 2：
输入： words = ["a","ab","abc","d","cd","bcd","abcd"]
输出：4
解释：这两个单词为 "ab", "cd"。

示例 3：
输入：words = ["a","aa","aaa","aaaa"]
输出：0
解释：不存在这样的两个单词。

提示：
2 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i] 仅包含小写字母
 */

/**
 * 1、二进制解法
 * - 之前使用的是一个26长度的bool数组，用来保存单个字符串中每个字母是否存在的标记位，也可以使用数字0和1来表示，正好对应二进制的值
 * - 这次使用int[]数组arr来保存，数组长度为words的长度，数组中每个单词中每个字母，他存在的位置使用数组arr中的具体位数来表示
 * -
 */
int maxProduct2(vector<string> &words)
{
  int size = words.size();
  vector<int> arr(size, 0);
  int res = 0;

  // 先遍历数组中的单词，并对每个单词中的字母进行记录到arr数组中去
  for (int i = 0; i < size; i++)
  {
    string word = words[i];
    for (int j = 0; j < word.length(); j++)
    {
      arr[i] |= 1 << (word[j] - 'a');
    }
  }

  // 两个单词比较
  for (int i = 0; i < words.size(); i++)
  {
    for (int j = i + 1; j < words.size(); j++)
    {
      string str1 = words[i];
      string str2 = words[j];

      if ((arr[i] & arr[j]) == 0)
      {
        int itemNum = str1.length() * str2.length();
        res = max(res, itemNum);
      }
    }
  }
  return res;
}

/**
 * 1、审题：输入一个由字符串组成的数组，现在需要从数组中找出两个字符串元素，要求两个字符串不能有相同的字母，且两个单词的长度乘积最长，并返回乘积的值
 * 2、解题：这个问题的核心在于找到两个单词，要求单词中的字母都不相同
 * - ① 朴素解法：
 * -- 两个单词两两比较， 接着比较两个单词中的字母再来两两比较是否存在相等的字母，时间复杂度为n^4，太多计算次数了，不符合要求
 * - ② 预先记录法：
 * -- 先遍历所有的字符串，记录每个字符串中每个字母是否出现过，使用二维数组，vector[i][26]=bool 记录每个单词，中每个位置是否存在该字母，如果存在则其值为true
 * -- 再使用两层for循环，找到需要比较的两个字符串，接着遍历26个字母，判断遍历到的该字母，再数组的位置i，和j位置的字符串是否存在该字母即可，如果都存在，则说明两个字符串都存在该字母，不符合要求
 * -- 如果没有同时存在，且求出他们的最后长度乘积的值
 */
int maxProduct1(vector<string> &words)
{
  int res = 0;
  int size = words.size();
  // 二维数据
  vector<vector<bool>> arr(size, vector<bool>(26, false));

  // 遍历数组中所有字符串，并标记字符串中该字母是否存在与否
  for (int i = 0; i < words.size(); i++)
  {
    string word = words[i];
    for (int j = 0; j < word.length(); j++)
    {
      char ch = word[j];
      arr[i][ch - 'a'] = true;
    }
  }

  // 找出需要比较的两两字符串
  for (int i = 0; i < words.size(); i++)
  {
    for (int j = i + 1; j < words.size(); j++)
    {
      string str1 = words[i];
      string str2 = words[j];

      // 遍历26个字母，判断该字母是否再两个字符串中是否都同时存在
      int k = 0;
      for (; k < 26; k++)
      {
        if (arr[i][k] && arr[j][k])
        {
          break;
        }
      }
      if (k == 26) // 都不存在，求他们的乘积
      {
        int itemNum = str1.length() * str2.length();
        res = max(res, itemNum);
      }
    }
  }
  return res;
}

int maxProduct(vector<string> &words)
{
  int res = 0;
  // 找出需要比较的两两字符串
  for (int i = 0; i < words.size(); i++)
  {
    for (int j = i + 1; j < words.size(); j++)
    {
      string str1 = words[i];
      string str2 = words[j];

      int m = 0;
      int n = 0;
      for (; m < str1.length(); m++)
      {
        n = 0;
        for (; n < str2.length(); n++)
        {
          if (str1[m] == str2[n])
          {
            break;
          }
        }
        if (n != str2.length())
        {
          break;
        }
      }

      if (m == str1.length() && n == str2.length())
      {
        int itemNum = str1.length() * str2.length();
        res = max(res, itemNum);
      }
    }
  }
  return res;
}

int main()
{
  std::cout << "《剑指》" << std::endl;
  vector<string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  auto res = maxProduct(words);
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
  //   for (auto element : ele)
  //   {
  //     std::cout << element << ",";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  // std::cout << "map +++++++++++++++ " << std::endl;
  // for (auto ele : map)
  // {
  //   std::cout << ele.first << " ---- nextNodes: " << std::endl;
  //   for (auto ele : ele.second)
  //   {
  //     std::cout << ele;
  //     std::cout << std::endl;
  //   }

  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  // std::cout << "inDegreeMap ============ " << std::endl;
  // for (auto ele : inDegreeMap)
  // {
  //   std::cout << ele.first << " ---- " << ele.second;
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  return 0;
}
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
LCR 117. 相似字符串组
https://leetcode.cn/problems/H6lPxb/description/

如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。
例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。
总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。
形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。
给定一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个 字母异位词 。请问 strs 中有多少个相似字符串组？
字母异位词（anagram），一种把某个字符串的字母的位置（顺序）加以改换所形成的新词。

示例 1：
输入：strs = ["tars","rats","arts","star"]
输出：2

示例 2：
输入：strs = ["omv","ovm"]
输出：1

提示：
1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i] 只包含小写字母。
strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。
 */

/**
 * 1、审题：输入一个字符串数组，数组中的字符串都是字母异位词，相似字符串意思是两个字符串中有两个字母不相同，其他位置的字母都相同
 * - 现在要将相似的字符串组合成一个子集，并将所有子集的个数返回
 * 2、解题：并查集解法
 * - 和上一题116类似的思路，遍历数组中的每个字符串，给每个字符串设置他的根节点是自己，并且子集的个数也是n
 * - 然后两层for循环遍历节点，让每个单词和后面位置的字符串进行比较，这样没两个单词之间都有交集了，就判断他们的是否是相似字符串（存在两个不同的字母）
 * - 如果是相似字符串，则判断他们的根节点是否相同，不同的话需要将他们合并到一个子集中，并且所有子集个数减1，并最终返回
 */

/**
 * 判断两个字符串，是否是相似字符串
 * - 只有两个字母存在不同
 */
bool isSimile(string &str1, string &str2)
{
  int num = 2;
  for (int i = 0; i < str1.size(); i++)
  {
    if (str1[i] != str2[i])
    {
      num--;
    }
  }
  return num == 0;
}

int findFather(vector<int> &fathers, int i)
{
  if (fathers[i] == i)
  {
    return i; // 根节点是自己，返回去
  }
  int f = findFather(fathers, fathers[i]);
  fathers[i] = f;
  return fathers[i];
}

bool merge(vector<int> &fathers, int i, int j)
{
  int fI = findFather(fathers, i);
  int fJ = findFather(fathers, j);
  if (fI == fJ)
  {
    return false;
  }

  fathers[fI] = fJ;
  return true;
}

int numSimilarGroups(vector<string> &strs)
{
  int n = strs.size();
  int resNum = n;
  vector<int> fathers(n, 0);

  for (int i = 0; i < n; i++)
  {
    fathers[i] = i;
  }

  for (int i = 0; i < n; i++)
  {
    std::cout << " numSimilarGroups i: " << i << std::endl;
    for (int j = i + 1; j < n; j++)
    {
      std::cout << " numSimilarGroups ------- j: " << j << std::endl;
      // 如果两个字母相等，则直接合并
      if (strs[i] == strs[j])
      {
        std::cout << " strs[i] == strs[j] ------- j: " << j << std::endl;
        if (merge(fathers, i, j))
        {
          resNum--;
        }
        continue;
      }

      if (isSimile(strs[i], strs[j]) && merge(fathers, i, j))
      {
        resNum--;
      }
    }
  }
  return resNum;
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
  vector<string> words = {"tars", "rats", "arts", "star"};

  // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
  // vector<vector<int>> prerequisites = {
  //     {1, 0},
  //     {2, 0},
  //     {3, 1},
  //     {3, 2},
  // };

  // vector<int> nums = {1, 2, 3};
  // vector<vector<int>> isConnected = {
  //     {1, 0, 0, 1},
  //     {0, 1, 1, 0},
  //     {0, 1, 1, 1},
  //     {1, 0, 1, 1},
  // };
  // vector<vector<int>> isConnected = {
  //     {1, 1, 0},
  //     {1, 1, 0},
  //     {0, 0, 1},
  // };

  auto res = numSimilarGroups(words);
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
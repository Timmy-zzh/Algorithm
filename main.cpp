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
LCR 114. 火星词典
https://leetcode.cn/problems/Jf1JuT/description/

现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同。
给定一个字符串列表 words ，作为这门语言的词典，words 中的字符串已经 按这门新语言的字母顺序进行了排序 。
请你根据该词典还原出此语言中已知的字母顺序，并 按字母递增顺序 排列。若不存在合法字母顺序，返回 "" 。若存在多种可能的合法字母顺序，返回其中 任意一种 顺序即可。
字符串 s 字典顺序小于 字符串 t 有两种情况：
在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t 中字母之前，那么 s 的字典顺序小于 t 。
如果前面 min(s.length, t.length) 字母都相同，那么 s.length < t.length 时，s 的字典顺序也小于 t 。

示例 1：
输入：words = ["wrt","wrf","er","ett","rftt"]
输出："wertf"

示例 2：
输入：words = ["z","x"]
输出："zx"

示例 3：
输入：words = ["z","x","z"]
输出：""
解释：不存在合法字母顺序，因此返回 ""。

提示：
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] 仅由小写英文字母组成
 */

/**
 * 1、审题：输入一个单词数组，数组中的每个单词都是已经排好序的列表，和我们平常使用的字母排序不一样，他有自己的规则，现在要求根据已有的字符串排序，
 * - 找出所有字母正确的排序顺序并输出
 * 2、解题：拓扑排序算法
 * - 可以根据提供的字符串数组，在遍历的时候，两两进行比对，找到前后两个字母的前后顺序关系，如果发现前面的字母相同，则顺序查找后面不同的字母，
 * - 这样就得到了所有字母，其中两个字母两两之间的依赖关系，根据这个前后顺序关系，可以进行拓扑排序算法，根据入度，出度关系找出他们的顺序结果
 * - 上面的步骤，只要找到两个字母的前后顺序关系，就可以将问题转换到113的课程表的问题。
 */

bool startsWith(const std::string &str, const std::string &prefix)
{
  return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

string alienOrder(vector<string> &words)
{
  for (auto ele : words)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;
  // 根据words字符串列表，找到相邻字符中两个字母的先后顺序，然后保存到集合中去
  std::map<char, int> inDegrees; // 每个字母对应的入度
  vector<vector<char>> chRules;

  // 先给每个字母设置入度=0
  for (int i = 0; i < words.size(); i++)
  {
    string str1 = words[i];

    for (int j = 0; j < str1.length(); j++)
    {
      char ch1 = str1[j];
      inDegrees[ch1] = 0;
    }
  }

  // 找到相邻字母之间的相互关系
  for (int i = 0; i < words.size() - 1; i++)
  {
    string str1 = words[i];
    string str2 = words[i + 1];

    if (startsWith(str1, str2) && str1 != str2)
    {
      std::cout << str1 << " === str1.find(str2) ==> " << str2 << std::endl;
      return "";
    }

    for (int j = 0; j < str1.length() && j < str2.length(); j++)
    {
      char ch1 = str1[j];
      char ch2 = str2[j];
      if (ch1 != ch2)
      {
        std::cout << str1 << " =====> " << str2 << " ,i:" << i << " ,j:" << j << std::endl;
        std::cout << ch1 << " =====> " << ch2 << std::endl;
        // 不等于，则 str1 中的字母顺序 小于 str2中的字母
        chRules.push_back({ch1, ch2});
        break;
      }
    }
  }

  // 根据字母先后关系，求出每个字母对应的入度 chRules
  for (auto rule : chRules)
  {
    char ch1 = rule[0];
    char ch2 = rule[1];

    if (inDegrees.find(ch2) != inDegrees.end())
    {
      inDegrees[ch2]++;
    }
    else
    {
      inDegrees[ch2] = 1;
    }
  }

  // 遍历1维数组
  for (auto ele : chRules)
  {
    std::cout << ele[0] << " --> " << ele[1];
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "inDegrees ====== " << std::endl;
  for (auto ele : inDegrees)
  {
    std::cout << ele.first << " ---- " << ele.second;
    std::cout << std::endl;
  }
  std::cout << std::endl;

  // 找到所有入度为0的字母，保存到队列queue中
  queue<char> queue;
  string resStr;

  for (auto &it : inDegrees)
  {
    if (it.second == 0)
    {
      queue.push(it.first);
    }
  }

  // 根据上面的两个数据，再使用while循环将队列中的字母数组取出来，进行拓扑排序
  while (!queue.empty())
  {
    auto node = queue.front();
    queue.pop();

    resStr += node;

    // 遍历 chRules ，找到 node指向的下一个字母

    for (auto rule : chRules)
    {
      char ch1 = rule[0];
      char ch2 = rule[1];

      if (ch1 == node)
      {
        inDegrees[ch2]--;
        if (inDegrees[ch2] == 0)
        {
          queue.push(ch2);
        }
      }
    }
  }

  return resStr.length() == inDegrees.size() ? resStr : "";
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  // vector<vector<int>> graph = {
  //     {1, 2},
  //     {3},
  //     {3},
  //     {},
  // };

  /**
输入: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
   */

  // vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
  // vector<string> words = {"z", "x", "z"};
  // vector<string> words = {"z", "z"};
  // vector<string> words = {"zy", "zx"};
  // vector<string> words = {"wrt", "wrtkj"};
  vector<string> words = {"ac", "ab", "b"};

  // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)

  // vector<vector<int>> prerequisites = {
  //     {1, 0},
  //     {2, 0},
  //     {3, 1},
  //     {3, 2},
  // };
  auto res = alienOrder(words);
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

  return 0;
}
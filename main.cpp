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
LCR 108. 单词接龙
https://leetcode.cn/problems/om3reC/description/

在字典（单词列表） wordList 中，从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列：
序列中第一个单词是 beginWord 。
序列中最后一个单词是 endWord 。
每次转换只能改变一个字母。
转换过程中的中间单词必须是字典 wordList 中的单词。
给定两个长度相同但内容不同的单词 beginWord 和 endWord 和一个字典 wordList ，找到从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0。

示例 1：
输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
输出：5
解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。

示例 2：
输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
输出：0
解释：endWord "cog" 不在字典中，所以无法进行转换。

提示：
1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord、endWord 和 wordList[i] 由小写英文字母组成
beginWord != endWord
wordList 中的所有字符串 互不相同
 */

/**
 * - 还是使用图的广度优先搜索算法，来计算开始单词到结束单词的距离
 * - 只不过不再使用map<string,vector<string>>数据结构来保存单词组成的图的关系，而是根据当前遍历的单词找出所有只改变一个单词的所有字符串，并保存到数组中
 * -- 如果单个单词的长度很多，那得出的数量是巨大的
 * - 然后去原始数组中wordList中查找是否存在
 * - 再使用一个vector数组来保存所有已经遍历过的单词
 * - 存在很多不必要的计算，因为算出的只变化一个字母的单词，数量太多了，需要优化
 */

bool canChange(const string &word1, const string &word2)
{
  // 遍历两个单词中不同字母的个数，差异数等于1返回true，否则返回false
  int num = 0;
  for (int i = 0; i < word1.size(); i++)
  {
    if (word1[i] != word2[i])
    {
      num++;
    }
  }
  return num == 1;
}

vector<string> getChangeWords(string &word, vector<string> &wordList)
{
  vector<string> changeWords;
  for (const auto &word2 : wordList)
  {
    if (canChange(word, word2))
    {
      changeWords.push_back(word2);
    }
  }

  // 遍历单词中的，每个单词，改变这一个单词，添加到数组中去
  // for (int i = 0; i < word.size(); i++)
  // {
  //   char ch = word[i];
  //   string temp = word;

  //   // 遍历26-1 = 25个字母，替换原先的字母，组成新的单词，添加到数组中去
  //   for (int j = 'a'; j <= 'z'; j++)
  //   {
  //     if (j == ch)
  //     {
  //       continue;
  //     }
  //     temp[i] = j;

  //     string newWord = temp;
  //     if (std::find(wordList.begin(), wordList.end(), newWord) == wordList.end())
  //     {
  //       continue;
  //     }
  //     changeWords.push_back(newWord);
  //   }
  // }
  return changeWords;
}

int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
  queue<string> queue;
  queue.push(beginWord);
  vector<string> visited; // 保存所有已遍历过的单词
  visited.push_back(beginWord);
  wordList.push_back(beginWord);

  int distance = 1;
  int size = 1;

  while (!queue.empty())
  {
    // 从队列中取出头部节点
    string item = queue.front();
    queue.pop();

    if (item == endWord)
    {
      return distance;
    }

    // 根据当前从队列中获取的单词item，获取所有可以与之变化一个字母的所有的相关单词的数组
    vector<string> changeWords = getChangeWords(item, wordList);

    // 遍历map
    std::cout << item << " ---> " << std::endl;
    for (auto ele : changeWords)
    {
      std::cout << ele << ",";
    }
    std::cout << std::endl;

    // 遍历这写所有的单词，看他是否在原始数组中是否存在
    for (const auto &changeWord : changeWords)
    {
      // if (std::find(wordList.begin(), wordList.end(), changeWord) == wordList.end()) // 数组中不存在
      // {
      //   continue;
      // }

      // 存在，判断之前是否遍历过
      if (std::find(visited.begin(), visited.end(), changeWord) != visited.end()) // 数组中存在，说明遍历过
      {
        continue;
      }

      // 添加到队列中
      queue.push(changeWord);
      visited.push_back(changeWord);
    }

    size--;
    if (size == 0)
    {
      distance++;
      size = queue.size();
    }
  }

  return 0;
}

/**
 * 1、审题：输入一个开始单词beginWord，和一个结束单词endWord，要求从开始单词经过变化能够最终变成结束单词
 * - 其中每次变化一个单词字母，并且要求变化后的单词要求是提供的单词数组wordList中的一个，求变化的次数，如果变化不了，返回0
 * 2、可采用图的广度优先算法来实现
 * - 将单词数组中的元素，转成图的链接表结构，使用map<string,vector<string>> 保存key表示的单词，和与之可以变化后的单词列表，将他们形成关系网
 * - 在以邻接表数据结构为基准求开始单词到结束单词的距离
 * - 先判断单词数组中是否包含结束单词，没有包含那永远也转换不过来
 * 3、总结：
 * - 使用计数法来计算每一圈结束的位置，比插入特殊节点更加准确，因为插入的特殊节点可能会与原始节点发生错乱
 * - 也可以使用两个队列，交换着来处理
 * - 当前想不明白的到时间后就暂停，不再继续想了，说不定明天再来就想出解决办法了
 * 4、改进方式：
 * - 使用邻接矩阵来表四单词之间的转换关系
 */

int ladderLength2(string beginWord, string endWord, vector<string> &wordList)
{

  std::cout << "ladderLength" << std::endl;

  if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end()) // 单词数组不包含结束单词
  {
    return 0;
  }

  std::map<string, vector<string>> map;

  // 构建单词和 与之关联的单词数组
  // 先从开始单词beginWord开始
  vector<string> lists;
  for (const auto word : wordList)
  {
    if (canChange(beginWord, word))
    {
      lists.push_back(word);
    }
  }
  if (lists.size() == 0)
  {
    return 0;
  }
  map[beginWord] = lists;

  // 在遍历数组中的其他单词
  wordList.push_back(beginWord);
  for (const auto currWord : wordList)
  {
    if (currWord == beginWord)
    {
      continue;
    }
    vector<string> lists;
    for (const auto word : wordList)
    {
      if (canChange(currWord, word))
      {
        lists.push_back(word);
      }
    }
    map[currWord] = lists;
  }

  // 遍历map
  for (const auto &pair : map)
  {
    std::cout << pair.first << " ---> " << std::endl;
    for (auto ele : pair.second)
    {
      std::cout << ele << ",";
    }
    std::cout << std::endl;
  }

  // 现在需要根据链接表map，求从开始单词到结束单词的距离，
  // 还要使用一个map<string,bool> 用于标记当前单词是否遍历过
  queue<string> queue;
  std::map<string, bool> visited;

  for (const string &word : wordList)
  {
    visited[word] = false;
  }

  queue.push(beginWord);
  int size = 1;
  int distance = 1;
  visited[beginWord] = true;

  while (!queue.empty())
  {
    string item = queue.front();
    queue.pop();

    if (item == endWord)
    {
      return distance;
    }

    // 根据map找到当前单词的关联单词数组
    vector<string> itemList = map[item];
    for (const string &word : itemList)
    {
      if (visited[word]) // 已经遍历过了
      {
        continue;
      }
      queue.push(word);
      visited[word] = true;
    }

    size--;
    if (size == 0)
    {
      distance++;
      size = queue.size();
    }
  }

  return 0;
}

int ladderLength1(string beginWord, string endWord, vector<string> &wordList)
{

  std::cout << "ladderLength" << std::endl;

  if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end()) // 单词数组不包含结束单词
  {
    return 0;
  }

  std::map<string, vector<string>> map;

  // 构建单词和 与之关联的单词数组
  // 先从开始单词beginWord开始
  vector<string> lists;
  for (const auto word : wordList)
  {
    if (canChange(beginWord, word))
    {
      lists.push_back(word);
    }
  }
  if (lists.size() == 0)
  {
    return 0;
  }
  map[beginWord] = lists;

  // 在遍历数组中的其他单词
  wordList.push_back(beginWord);
  for (const auto currWord : wordList)
  {
    if (currWord == beginWord)
    {
      continue;
    }
    vector<string> lists;
    for (const auto word : wordList)
    {
      if (canChange(currWord, word))
      {
        lists.push_back(word);
      }
    }
    map[currWord] = lists;
  }

  // 遍历map
  for (const auto &pair : map)
  {
    std::cout << pair.first << " ---> " << std::endl;
    for (auto ele : pair.second)
    {
      std::cout << ele << ",";
    }
    std::cout << std::endl;
  }

  // 现在需要根据链接表map，求从开始单词到结束单词的距离，
  // 还要使用一个map<string,bool> 用于标记当前单词是否遍历过
  queue<string> queue;
  std::map<string, bool> visited;

  for (const string &word : wordList)
  {
    visited[word] = false;
  }

  queue.push(beginWord);
  int size = 1;
  int distance = 1;
  visited[beginWord] = true;

  while (!queue.empty())
  {
    string item = queue.front();
    queue.pop();

    if (size == 0)
    {
      distance++;
      size = queue.size();
    }
    else
    {
      size--;
    }

    // 根据map找到当前单词的关联单词数组
    vector<string> itemList = map[item];
    for (const string &word : itemList)
    {
      if (visited[word])
      {
        // 已经遍历过了
        continue;
      }
      if (word == endWord)
      {
        return distance + 1;
      }

      queue.push(word);
      visited[word] = true;
    }
  }

  return 0;
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
  // vector<string> wordList = {"hot", "dot", "tog", "cog"};

  auto res = ladderLength("hit", "cog", wordList);

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
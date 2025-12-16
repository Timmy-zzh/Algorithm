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

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

/**
LCR 063. 单词替换
https://leetcode.cn/problems/UhWRSj/description/

在英语中，有一个叫做 词根(root) 的概念，它可以跟着其他一些词组成另一个较长的单词——我们称这个词为 继承词(successor)。
例如，词根an，跟随着单词 other(其他)，可以形成新的单词 another(另一个)。
现在，给定一个由许多词根组成的词典和一个句子，需要将句子中的所有继承词用词根替换掉。如果继承词有许多可以形成它的词根，则用最短的词根替换它。
需要输出替换之后的句子。

示例 1：
输入：dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
输出："the cat was rat by the bat"

示例 2：
输入：dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
输出："a a b c"

示例 3：
输入：dictionary = ["a", "aa", "aaa", "aaaa"], sentence = "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa"
输出："a a a a a a a a bbb baba a"

示例 4：
输入：dictionary = ["catt","cat","bat","rat"], sentence = "the cattle was rattled by the battery"
输出："the cat was rat by the bat"

示例 5：
输入：dictionary = ["ac","ab"], sentence = "it is abnormal that this solution is accepted"
输出："it is ab that this solution is ac"
 */

/**
 * 1、审题：
 * - 输入一组字符串数组，和单独的一句话（也是字符串），现在要求在一字符串数组中的子树作为词根，当句子中的单个字符串中存在前缀和词根相同的情况，
 * -- 则该字符串使用词根进行替换，并返回替换后的字符串
 * 2、解题：
 * - 涉及到字符串前缀搜索，使用前缀树进行解决
 * - 先根据字符串词根数组，构建前缀树，TrieNode为前缀树节点
 * - 再遍历句子，根据空格将句子拆分为单个的字符串数组并进行遍历，遍历过程中获取到的字符串，在前缀树中进行搜索，判断是否存在前缀词根
 * -- 存在的话返回词根，否则返回空字符串
 * - 最后将替换后的字符串数组重新组合成字符串，使用空格间隔
 */

/**
 * 在前缀树中查找单个字符串是否存在对应前缀
 * - 遍历字符串中字符，判断该字符对应的结点是否有空，如果为空，说明没有，直接返回空
 * - 如果存在该结点，则继续遍历，并判断该结点是否是单词结尾，是的话返回当前前缀
 * - 使用一个字符串保存遍历过的前缀
 */
string findPrex(TrieNode &root, string &word)
{
  std::string res = "";
  TrieNode *node = &root;
  for (auto ch : word)
  {
    int index = ch - 'a';
    if (node->isWord)
    {
      return res;
    }
    if (node->children[index] == nullptr)
    {
      break;
    }
    else
    {
      node = node->children[index];
      res += ch;
    }
  }
  return node->isWord ? res : "";
}

/**
 * 构造前缀树，遍历字符串数组，再遍历单个字符串中的字符
 * 根据单个字符判断前缀树节点是否存在，不存在则新创建前缀树节点，并重新赋值node
 * 最后设置节点的isWord标记为true
 */
TrieNode *buildTrie(vector<string> &dictionary)
{
  TrieNode *root = new TrieNode();
  TrieNode *node = nullptr;
  for (auto &word : dictionary)
  {
    node = root;
    for (auto &ch : word)
    {
      int index = ch - 'a';
      if (node->children[index] == nullptr)
      {
        node->children[index] = new TrieNode();
      }
      node = node->children[index];
    }
    node->isWord = true;
  }
  return root;
}

/**
 * 根据空格，将字符串拆分成字符串数组
 */
std::vector<std::string> splitBySpace(const std::string &sentence)
{
  std::vector<std::string> words;
  std::istringstream iss(sentence);
  std::string word;

  while (iss >> word)
  {
    words.push_back(word);
  }
  return words;
}

std::string joinWords(const std::vector<std::string> &words)
{
  std::ostringstream oss;
  // 遍历所有单词
  for (size_t i = 0; i < words.size(); ++i)
  {
    if (i > 0)
    {
      oss << " "; // 在单词间添加空格 -- 在单词前面加空格，除了第一个单词
    }
    oss << words[i];
  }

  return oss.str();
}

string replaceWords(vector<string> &dictionary, string sentence)
{
  TrieNode *root = buildTrie(dictionary);
  // 分割句子成字符串数组
  std::vector<std::string> words = splitBySpace(sentence);
  // 遍历字符串数组
  for (int i = 0; i < words.size(); i++)
  {
    std::string word = words[i];
    // 根据单个字符串，查找词根
    std::string prexStr = findPrex(*root, word);
    if (!prexStr.empty())
    {
      words[i] = prexStr;
    }
  }
  return joinWords(words);
}

int main()
{
  std::cout << "Hello, Algorithm!" << std::endl;

  // vector<string> matrix = {"10100", "10111", "11111", "10010"};

  // for (auto ele : matrix)
  // {
  //   std::cout << ele << ",";
  // }
  // std::cout << std::endl;

  // auto res = maximalRectangle(matrix);

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
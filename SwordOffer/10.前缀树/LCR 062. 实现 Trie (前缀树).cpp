#include <iostream>
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
LCR 062. 实现 Trie (前缀树)
https://leetcode.cn/problems/QC3q1f/description/

Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：
Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

示例：
输入
inputs = ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
inputs = [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True

提示：
1 <= word.length, prefix.length <= 2000
word 和 prefix 仅由小写英文字母组成
insert、search 和 startsWith 调用次数 总计 不超过 3 * 104 次
 */

/**
 * 1、审题：前缀树实现，前缀树是一颗多叉树，如果规定前缀树节点值保存的小写字母，则多叉树的子树大小为26（26个英文字母个数）
 * 2、解题：
 * - 实现二叉树的字符串插入insert，字符串查询search，和前缀字符判断startsWith
 * - 在构造函数中，定义一个26个大小的数组，用于标示当前结点的子节点保存位置
 * - 当调用insert方法插入字符串时，先找到根节点，遍历字符串，并从前缀树的根节点开始判断，遍历到的字符在前缀树中是否存在，如果不存在则新建该字符标识的结点
 * -- 直到字符串全部遍历完，并将该结点标识为是单个单词
 * - 查询方法search和前缀树内容判断，也是类似的思路
 */
class Trie
{

public:
    Trie()
    {
        root = new TrieNode();
    }

    class TrieNode // 内部类
    {
    public:
        bool isWord = false;
        TrieNode *children[26]; // 数组

        TrieNode()
        {
            for (int i = 0; i < 26; i++)
            {
                children[i] = nullptr;
            }
        }

        ~TrieNode()
        {
            for (int i = 0; i < 26; i++)
            {
                delete children[i];
                children[i] = nullptr;
            }
        }
    };

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        TrieNode *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            int index = word[i] - 'a';
            if (node->children[index] == nullptr)
            {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isWord = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        TrieNode *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            int index = word[i] - 'a';
            if (node->children[index] == nullptr)
            {
                return false;
            }
            node = node->children[index];
        }
        return node->isWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        TrieNode *node = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            int index = prefix[i] - 'a';
            if (node->children[index] == nullptr)
            {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }

private:
    TrieNode *root;
};

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
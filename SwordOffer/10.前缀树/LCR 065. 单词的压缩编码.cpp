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
LCR 065. 单词的压缩编码
https://leetcode.cn/problems/iSwD2y/description/

单词数组 words 的 有效编码 由任意助记字符串 s 和下标数组 indices 组成，且满足：

words.length == indices.length
助记字符串 s 以 '#' 字符结尾
对于每个下标 indices[i] ，s 的一个从 indices[i] 开始、到下一个 '#' 字符结束（但不包括 '#'）的 子字符串 恰好与 words[i] 相等
给定一个单词数组 words ，返回成功对 words 进行编码的最小助记字符串 s 的长度 。

示例 1：
输入：words = ["time", "me", "bell"]
输出：10
解释：一组有效编码为 s = "time#bell#" 和 indices = [0, 2, 5] 。
words[0] = "time" ，s 开始于 indices[0] = 0 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[1] = "me" ，s 开始于 indices[1] = 2 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[2] = "bell" ，s 开始于 indices[2] = 5 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"

示例 2：
输入：words = ["t"]
输出：2
解释：一组有效编码为 s = "t#" 和 indices = [0] 。

提示：
1 <= words.length <= 2000
1 <= words[i].length <= 7
words[i] 仅由小写字母组成
 */

/**
 * 构建前缀树
 * - 以单词的逆序遍历添加节点
 */
TrieNode *buildTrie(vector<string> &words)
{
    TrieNode *root = new TrieNode();
    TrieNode *node = nullptr;
    for (auto word : words)
    {
        node = root;
        // 逆序遍历单个单词
        for (int i = word.length() - 1; i >= 0; --i)
        {
            int pos = word[i] - 'a';
            if (node->children[pos] == nullptr)
            {
                node->children[pos] = new TrieNode();
            }
            node = node->children[pos];
        }
        node->isWord = true;
    }
    return root;
}

/**
 * 深度优先遍历，将每个路径的结点个数添加到path中
 * @param node 当前遍历到的结点位置
 * @param path 遍历到当前结点，到根节点，这条路径的结点个数
 * @param pathSum 所有路径的结点和，要求当遍历到叶子结点时，这个数据才会增加
 *
 */
void dfs(TrieNode *node, int path, int &pathSum)
{
    // 遍历前缀树节点值，一直到叶子结点
    bool isLeaf = true; // 判断当前遍历到的结点是否是叶子结点
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != nullptr)
        {
            isLeaf = false;
            dfs(node->children[i], path + 1, pathSum);
        }
    }
    if (isLeaf)
    {
        pathSum += path;
    }
}

/**
 * 1、审题：
 * - 输入一个字符串数组，返回压缩后的编码字符串的长度，编码规则是每个单词以#结尾拼接，当遇到相同子字符串和其他字符串相同情况时合并一处记录
 * 2、解题：
 * - 因为题目的编码规则是单词与子字符串相同则合并一处，并且结果只要求返回编码后的字符串长度，可以变换成两个单词的前缀相同即可，
 * - 在构建前缀树时，根据单次的逆序字符创建前缀树，
 * - 并进行dfs深度优先遍历，直到叶子结点，使用一个全局变量记录整个路径上的结点个数。
 */
int minimumLengthEncoding(vector<string> &words)
{
    TrieNode *root = buildTrie(words);
    root->print();
    int pathSum = 0;
    dfs(root, 1, pathSum);
    return pathSum;
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
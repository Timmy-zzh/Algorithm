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
LCR 064. 实现一个魔法字典
https://leetcode.cn/problems/US1pGT/description/

设计一个使用单词列表进行初始化的数据结构，单词列表中的单词 互不相同 。
如果给出一个单词，请判定能否只将这个单词中一个字母换成另一个字母，使得所形成的新单词存在于已构建的神奇字典中。

实现 MagicDictionary 类：
MagicDictionary() 初始化对象
void buildDict(String[] dictionary) 使用字符串数组 dictionary 设定该数据结构，dictionary 中的字符串互不相同
bool search(String searchWord) 给定一个字符串 searchWord ，判定能否只将字符串中 一个 字母换成另一个字母，
使得所形成的新字符串能够与字典中的任一字符串匹配。如果可以，返回 true ；否则，返回 false 。


示例：
输入
inputs = ["MagicDictionary", "buildDict", "search", "search", "search", "search"]
inputs = [[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
输出
[null, null, false, true, false, false]

解释
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // 返回 False
magicDictionary.search("hhllo"); // 将第二个 'h' 替换为 'e' 可以匹配 "hello" ，所以返回 True
magicDictionary.search("hell"); // 返回 False
magicDictionary.search("leetcoded"); // 返回 False
 */

/**
 * 1、审题：
 * - 构建一个类，首先输入一个字符串数组作为基础数据，然后调用search查询方法，根据输入的查询参数，
 * - 判断是否存在值修改参数字符串中的一个字母就可以匹配到基础数据中的一个字符串
 * 2、解题：
 * 解法一：遍历解法
 * - 使用数组保存字符串基础数据，在查询方法search中，使用两层for循环，
 * - 第一层for循环为从基础数据数组中，遍历到一个字符串，然后与查询字符串进行内部字符的比较
 * - 内层for循环则为字符的比较，使用变量diff标记当前两个字符串存在不同的字符个数，如果超过1个以上则直接返回false
 * -- 如果遍历到结束，并且diff只有1个不相同的字符，则命中选择返回true
 */
class MagicDictionary
{
public:
    MagicDictionary()
    {
    }

    void buildDict(vector<string> dictionary)
    {
        m_words = dictionary;
    }

    bool search(string searchWord)
    {
        int diff;
        for (auto &word : m_words)
        {
            diff = 0;
            if (word.length() != searchWord.length()) // 先判断字符串长度
            {
                continue; // 当前单词长度不一致，则继续遍历后面的字符串
            }

            // 比较word，和searchWord相同位置的字符是否相同，不相同diff变量递增
            for (int i = 0; i < word.length(); i++)
            {
                if (word[i] != searchWord[i])
                {
                    diff++;
                    if (diff > 1)
                    {
                        break; // 当前两个字符串中字符不相同的个数超过1个，不再继续进行判断
                    }
                }
            }

            // 遍历结束后，判断不相同的字符是否只有一个
            if (diff == 1)
            {
                return true;
            }
        }
        return false;
    }
    std::vector<std::string> m_words;
};

/**
 * 解法二：递归实现
 * - 使用前缀树进行构建
 * - 然后在查询方法时，使用dfs进行深度优先遍历，遍历过程中分情况：
 * -- 1、遍历到单词结束，节点也结束，并且中间有变更一次，则命中了
 * -- 2、遍历到单词和节点值不一样，则变更一次，每个字符有26个字母选择项，要寻找到有节点的下一个节点值
 * -- 3、直到遍历到空节点或者字符串和节点为单词结尾的位置
 */
class MagicDictionary
{
public:
    MagicDictionary() : root(new TrieNode())
    {
    }
    ~MagicDictionary()
    {
        delete root;
        root = nullptr;
    }

    /**
     * 构建前缀树
     * - 双层for循环，外层for循环遍历字符串数组，内层for循环遍历每个字符串中的字符
     * - 并且在字符的位置新建结点
     */
    void buildDict(vector<string> dictionary)
    {
        TrieNode *node = nullptr;
        for (auto word : dictionary)
        {
            node = root;
            for (int i = 0; i < word.length(); i++)
            {
                int index = word[i] - 'a';
                // 判断当前遍历到字符的结点是否存在，不存在则新建
                if (node->children[index] == nullptr)
                {
                    node->children[index] = new TrieNode();
                }
                // 当前结点赋值，一直往前缀树下一层行走
                node = node->children[index];
            }
            node->isWord = true;
        }
    }

    bool dfs(TrieNode *node, const string &searchWord, int pos, bool isChange)
    {
        // 当前结点为空，遍历到空节点了
        if (node == nullptr || pos > searchWord.length())
        {
            return false;
        }

        // 查询位置i遍历到字符串末尾了，并且遍历到的结点为单词结尾标记
        if (pos == searchWord.length() && node->isWord && isChange)
        {
            return true;
        }

        // 遍历当前结点的子节点，从26个子节点中查找，只要其中有一个满足条件的就返回true
        // 碰到相同的字符，则直接传入isChange，如果不同则isChange需要判断和变更处理
        for (int i = 0; i < 26; i++)
        {
            // 判断26个子节点中是否为空
            bool newChange = false;
            if (searchWord[pos] == (i + 'a')) // 字符相同，则直接使用isChange
            {
                newChange = isChange;
            }
            else
            {
                // 如果不同，则判断isChange是否变更过，变更过又遇到不同的，直接过滤了
                if (isChange)
                {
                    continue;
                }
                else
                {
                    newChange = true;
                }
            }

            if (dfs(node->children[i], searchWord, pos + 1, newChange))
            {
                return true;
            }
        }

        return false;
    }

    /**
     * 字符串查询：
     * - 从根节点开始遍历，并记录当前遍历到的字符位置，和字符串中单个字符是由有变更的标记
     */
    bool search(string searchWord)
    {
        return dfs(root, searchWord, 0, false);
    }

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
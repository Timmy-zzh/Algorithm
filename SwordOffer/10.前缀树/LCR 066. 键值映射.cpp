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
// #include "src/bean.h"

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
LCR 066. 键值映射
https://leetcode.cn/problems/z1R5dt/description/


实现一个 MapSum 类，支持两个方法，insert 和 sum：
MapSum() 初始化 MapSum 对象
void insert(String key, int val) 插入 key-val 键值对，字符串表示键 key ，整数表示值 val 。如果键 key 已经存在，那么原来的键值对将被替代成新的键值对。
int sum(string prefix) 返回所有以该前缀 prefix 开头的键 key 的值的总和。

示例：
输入：
inputs = ["MapSum", "insert", "sum", "insert", "sum"]
inputs = [[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
输出：
[null, null, 3, null, 5]
解释：
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);
mapSum.sum("ap");           // return 3 (apple = 3)
mapSum.insert("app", 2);
mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)

提示：
1 <= key.length, prefix.length <= 50
key 和 prefix 仅由小写英文字母组成
1 <= val <= 1000
最多调用 50 次 insert 和 sum
 */

/**
 * 1、审题：实现一个类，包含两个方法，一个插入insert方法，参数是一个字符串和对应的数字val
 * - 还有一个是搜索方法sum，参数也是字符串，返回以该字符串为前缀的所欲单词对应的数字总和
 * 2、解题：
 * - 创建前缀树节点，每个节点保存一个对应的数字value，当插入一个完整的单词最后的结点时，设置他的value值为对应数字
 * - 调用sum方法时，从根节点开始查找到前缀末尾的结点，然后深度遍历该结点为前缀的所有结点值的和
 */

/**
 * 当前结点对应的vlaue值
 * 和child子节点，使用数组保存
 */
class TrieNode
{
public:
    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
        value = 0;
    };
    ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            delete children[i];
            children[i] = nullptr;
        }
    };

public:
    TrieNode *children[26];
    int value;
};

class MapSum
{
public:
    MapSum()
    {
        root = new TrieNode();
    }

    /**
     * 前缀树插入单词
     * - 遍历单词所有字符，和前缀树的结点，判断结点是否存在，不存在则创建
     * - 最后结点value属性进行赋值
     */
    void insert(string key, int val)
    {
        TrieNode *node = root;
        for (int i = 0; i < key.length(); i++)
        {
            int pos = key[i] - 'a';
            if (node->children[pos] == nullptr)
            {
                node->children[pos] = new TrieNode();
            }
            node = node->children[pos];
        }
        node->value = val;
    }

    /**
     * 1、先查找到已prefix字符串为前缀树的最后的一个节点
     * 2、然后dfs深度优先遍历，所有的单词，并返回所有的结点累计和
     */
    int sum(string prefix)
    {
        TrieNode *node = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            int pos = prefix[i] - 'a';
            if (node->children[pos] != nullptr)
            {
                node = node->children[pos];
            }
            else
            {
                return 0; // 不存在以该字符串为前缀的结点
            }
        }

        return getSum(node);
    }

    int getSum(TrieNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int sum = node->value;
        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                sum += getSum(node->children[i]);
            }
        }
        return sum;
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
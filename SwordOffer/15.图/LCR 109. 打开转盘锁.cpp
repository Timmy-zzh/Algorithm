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
LCR 109. 打开转盘锁
https://leetcode.cn/problems/zlDJc7/description/

一个密码锁由 4 个环形拨轮组成，每个拨轮都有 10 个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。
每个拨轮可以自由旋转：例如把 '9' 变为 '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 target 代表可以解锁的数字，请给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 -1 。

示例 1：
输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，因为当拨动到 "0102" 时这个锁就会被锁定。

示例 2：
输入: deadends = ["8888"], target = "0009"
输出：1
解释：
把最后一位反向旋转一次即可 "0000" -> "0009"。

示例 3：
输入: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
输出：-1
解释：
无法旋转到目标数字且不被锁定。

示例 4：
输入: deadends = ["0000"], target = "8888"
输出：-1

提示：
1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target 不在 deadends 之中
target 和 deadends[i] 仅由若干位数字组成
 */

/**
 * 1、审题：输入一个字符串数组和目标字符串，每个字符串代表一个转轮密码锁的密码数值，初始密码为0000，数组中的字符串值为转轮锁的死锁状态值，需要规避
 * - 现在要求从初始密码不断波动每个转轮，求最少波动次数能够从初始密码转动到目标密码值，并且中途要求避开死锁状态密码值
 * 2、解题：采用广度优先算法
 * - 将每个密码锁值看做是一个节点，当前密码锁可以转变后的字符串，看成是与之相连的节点值，这样就形成了一个图的数据结构了。
 * - 就将题目转化成从开始节点0000，到目标节点 target节点需要的最短路径，且中途需要过滤掉死锁状态值，
 * - 先判断死锁状态是否包含起始节点，如果刚开始就是死锁状态，直接返回-1
 * - 使用queue队列保存遍历到的节点，采用广度优先搜索算法bfs，不断从开始节点扩散到周围的节点列表，直到遇到目标节点
 * -- 使用size值来记录当前遍历的圈层的节点个数，使用distance来记录从开始节点到当前圈层的路径长度，
 * - 也可以使用双向遍历来从开始节点和目标节点两个方向同时进行搜索，这样可以避免很多不必要的节点搜索
 */
vector<string> getNearNodes(const string &node)
{
    vector<string> nearNodes;
    for (int i = 0; i < node.length(); i++)
    {
        char ch = node[i];
        // 将char转成int类型
        int number = ch - '0';

        if (number == 0)
        {
            string temp = node;
            temp[i] = '1';
            nearNodes.push_back(temp);

            string temp2 = node;
            temp2[i] = '9';
            nearNodes.push_back(temp2);
        }
        else if (number == 9)
        {
            string temp = node;
            temp[i] = '0';
            nearNodes.push_back(temp);

            string temp2 = node;
            temp2[i] = '8';
            nearNodes.push_back(temp2);
        }
        else
        {
            string temp = node;
            temp[i] = ch + 1;
            nearNodes.push_back(temp);

            string temp2 = node;
            temp2[i] = ch - 1;
            nearNodes.push_back(temp2);
        }
    }

    return nearNodes;
}

int openLock(vector<string> &deadends, string target)
{
    const string start = "0000";
    if (std::find(deadends.begin(), deadends.end(), start) != deadends.end()) // 开始节点为死锁状态
    {
        return -1;
    }

    queue<string> queue;
    queue.push(start);
    int size = 1;
    int distance = 0;
    vector<string> visited; // 已经遍历过的节点
    visited.push_back(start);

    while (!queue.empty())
    {
        string node = queue.front();
        queue.pop();

        if (node == target)
        {
            return distance;
        }

        // 根据当前遍历到的节点node，查找周围的节点
        vector<string> nearNodes = getNearNodes(node);

        // 遍历map
        std::cout << node << " ---> " << std::endl;
        for (auto ele : nearNodes)
        {
            std::cout << ele << ",";
        }
        std::cout << std::endl;

        for (auto nearNode : nearNodes)
        {
            if (std::find(visited.begin(), visited.end(), nearNode) != visited.end()) // 已经遍历过了
            {
                continue;
            }

            // 还要避开死锁状态值
            if (std::find(deadends.begin(), deadends.end(), nearNode) != deadends.end())
            {
                continue;
            }

            queue.push(nearNode);
            visited.push_back(nearNode);
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

int main()
{
    std::cout << "《剑指》" << std::endl;

    vector<string> wordList = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
    // vector<string> wordList = {"0201", "0101", "0102", "1212", "2002"};
    // vector<string> wordList = {"8888"};

    auto res = openLock(wordList, "8888");

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
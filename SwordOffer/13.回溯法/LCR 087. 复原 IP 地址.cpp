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
LCR 087. 复原 IP 地址
https://leetcode.cn/problems/0on3uN/description/

给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能从 s 获得的 有效 IP 地址 。你可以按任何顺序返回答案。
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。

示例 1：
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]

示例 2：
输入：s = "0000"
输出：["0.0.0.0"]

示例 3：
输入：s = "1111"
输出：["1.1.1.1"]

示例 4：
输入：s = "010010"
输出：["0.10.0.10","0.100.1.0"]

示例 5：
输入：s = "10203040"
输出：["10.20.30.40","102.0.30.40","10.203.0.40"]

提示：
0 <= s.length <= 3000
s 仅由数字组成
 */

/**
 * 1、审题：输入一个由数字组成的字符串，這个字符串表示一个IP地址的纯数字，现在要求将该字符串以三个点号进行分割，
 * - 并且要求分割后的数字大小要求从[0-255],且单独的数字不能以0开头
 * 2、解题：回溯法，递归函数实现
 * - 将题目转换成插入三个点，在遍历的过程中记录开始的位置start，和已经插入的点的个数（刚开始点数为3，直到dot数量为0）
 * - 分割的时候注意分割后的数字是否符合条件
 */

bool checkNumStr(string &numStr)
{
    if (numStr == "")
    {
        return false;
    }
    if (numStr == "0")
    {
        return true;
    }
    if (numStr[0] == '0')
    {
        return false;
    }
    if (numStr.length() > 3)
    {
        return false;
    }

    int num = std::stoi(numStr);
    if (num > 255)
    {
        return false;
    }
    return true;
}

void helper(string &s, int dot, int start, vector<string> &item, vector<string> &res)
{
    std::cout << "111 helper dot:" << dot << " start:" << start << std::endl;
    if (dot == 0 && start == s.length())
    {
        // 将item中的字符串拼接成字符串，保存到res中
        string itemStr = "";
        for (int i = 0; i < item.size(); i++)
        {
            itemStr += item[i];
            if (i != item.size() - 1)
            {
                itemStr += ".";
            }
        }
        res.push_back(itemStr);
        return;
    }

    if (dot < 0)
    {
        return;
    }

    for (int i = start; (i < s.length() && i < start + 3); i++) // 单个数字控制在三位数
    {
        string numStr = s.substr(start, i - start + 1);
        std::cout << "222 for numStr:" << numStr << " i:" << i << std::endl;
        // 判断当前截取的数字是否符合要求
        if (checkNumStr(numStr))
        {
            std::cout << "333 for numStr:" << numStr << std::endl;
            item.push_back(numStr);
            helper(s, dot - 1, i + 1, item, res);
            item.pop_back();
        }
    }
}

vector<string> restoreIpAddresses(string s)
{
    vector<string> res;
    vector<string> item;
    helper(s, 4, 0, item, res);
    return res;
}

int main()
{
    std::cout << "《剑指》" << std::endl;
    ListNode node1(4);
    ListNode node2(2);
    ListNode node3(1);
    ListNode node4(3);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node1.print();

    // auto res = sortArray(nums);
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
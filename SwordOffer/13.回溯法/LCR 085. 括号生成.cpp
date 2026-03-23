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
LCR 085. 括号生成
https://leetcode.cn/problems/IDBivT/description/

正整数 n 代表生成括号的对数，请设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]

示例 2：
输入：n = 1
输出：["()"]

提示：
1 <= n <= 8
 */

/**
 * 1、审题：输入数字n，表示要生成的括号的对数，要求返回可以生成的所有括号集合
 * 2、输入的数字n表示有n对括号，也就是有n个左括号和n个右括号
 * - 使用回溯法实现，这种数量固定的，可以使用递减法
 * - 当左右括号的数量不断减少到0时，则命中要求，当前组合的括号字符串为所求目标值
 * - 还需要准守两个规则，一个是左括号减少不能少于0否则可以继续插入左括号
 * - 第二个规则是当左括号已经存在的数量大于右括号的数量时，可以插入右括号进去
 */
void helper(int left, int right, string item, vector<string> &res)
{
    if (left == 0 && right == 0)
    {
        res.push_back(item);
        return;
    }

    if (left > 0) // 插入左括号
    {
        helper(left - 1, right, item + "(", res);
    }
    if (left < right) // 当前已存在的左括号多，可以插入右括号
    {
        helper(left, right - 1, item + ")", res);
    }
}

vector<string> generateParenthesis(int n)
{
    vector<string> res;
    helper(n, n, "", res);
    return res;
}

int main()
{
    std::cout << "《剑指offer》" << std::endl;
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
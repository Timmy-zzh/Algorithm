#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
#include <stack>
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
LCR 037. 行星碰撞
https://leetcode.cn/problems/XagZNi/description/

给定一个整数数组 asteroids，表示在同一行的小行星。
对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。
每一颗小行星以相同的速度移动。
找出碰撞后剩下的所有小行星。碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。
两颗移动方向相同的行星，永远不会发生碰撞。

示例 1：
输入：asteroids = [5,10,-5]
输出：[5,10]
解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。

示例 2：
输入：asteroids = [8,-8]
输出：[]
解释：8 和 -8 碰撞后，两者都发生爆炸。

示例 3：
输入：asteroids = [10,2,-5]
输出：[10]
解释：2 和 -5 发生碰撞后剩下 -5 。10 和 -5 发生碰撞后剩下 10 。

示例 4：
输入：asteroids = [-2,-1,1,2]
输出：[-2,-1,1,2]
解释：-2 和 -1 向左移动，而 1 和 2 向右移动。 由于移动方向相同的行星不会发生碰撞，所以最终没有行星发生碰撞。
 */

/**
 * 1、审题：输入一个int数组，数组中的整数元素表示行星的大小的运行方向，如果遇到相对方向的行星，则会发生碰撞
 * - 碰撞结果是大和小碰撞留下大的，相同大小的两个都想消失，求最后留下来的行星组成的数组
 * 2、解题：使用栈保留表示行星的整数
 * - 创建栈数据对象，遍历所有行星，当栈为空时，元素入栈，
 * - 当栈中已有元素，则判断表示元素行星的方向，两元素方向相同或相背不发生碰撞，元素入栈
 * - 如果两元素相对方向，则会发生碰撞，大的元素留下并入栈，元素相同则两个元素都小时
 * - 最后是将栈中的元素获取出来，注意取出的顺序
 */
vector<int> asteroidCollision(vector<int> &asteroids)
{
    std::vector<int> res;
    std::stack<int> stack;

    for (int i = 0; i < asteroids.size(); i++)
    {
        int num = asteroids[i];
        if (stack.empty())
        {
            stack.push(num);
        }
        else
        {
            // 栈中元素不为空，则取出
            while (!stack.empty())
            {
                int top = stack.top();
                std::cout << "i:" << i << " ,top:" << top << ",num:" << num << std::endl;
                // 判断top与num的方向是否相对

                if (top * num > 0) // 方向相同，入栈
                {
                    std::cout << "if (top * num > 0) // 方向相同，入栈" << std::endl;
                    stack.push(num);
                    break;
                }
                else if (top < 0 && num > 0)
                { // 方向不同，但是向背，前一个往左《0，后一个往右》0，不会碰撞
                    std::cout << "if (top < 0 && num > 0) 方向不同，但是向背" << std::endl;
                    stack.push(num);
                    break;
                }
                else
                {
                    std::cout << "方向相对了，需要比较大小" << std::endl;
                    // 方向相对了，需要比较大小
                    if (std::abs(num) == std::abs(top)) // 相等
                    {
                        stack.pop();
                        break;
                    }
                    else if (std::abs(top) > std::abs(num)) // 栈顶元素大
                    {
                        break;
                    }
                    else
                    { // 栈顶元素小，出栈继续比较
                        stack.pop();
                        if (stack.empty())
                        {
                            stack.push(num);
                            break;
                        }
                    }
                }
            }
        }
    }

    // 将栈中所有元素出栈，插入到vector中
    while (!stack.empty())
    {
        int top = stack.top();
        res.insert(res.begin(), top);
        stack.pop();
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // vector<string> timePoints = {"00:00", "23:59", "00:00"};
    // vector<int> timePoints = {5, 10, -5};
    vector<int> timePoints = {1, -2, -2, -2};
    for (auto element : timePoints)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    auto res = asteroidCollision(timePoints);
    // std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    for (auto element : res)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

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
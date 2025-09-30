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
LCR 038. 每日温度
https://leetcode.cn/problems/iIQa4I/description/

请根据每日 气温 列表 temperatures ，重新生成一个列表，要求其对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。
如果气温在这之后都不会升高，请在该位置用 0 来代替。

示例 1：
输入：temperatures = [73,74,75,71,69,72,76,73]
输出：[1,1,4,2,1,1,0,0]

示例 2：
输入：temperatures = [30,40,50,60]
输出：[1,1,1,0]

示例 3：
输入：temperatures = [30,60,90]
输出：[1,1,0]

提示：
1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
 */

/**
 * 1、审题：输入一个int数组，元素内容为每天的温度数据，要求前面的温度在后面最近几天能出现更高的温度，将距离的天数使用数组返回
 * 2、解题：
 * 1）、暴力解法
 * - 两层for循环，外层for循环遍历当天的温度，内层for循环遍历后面的温度，遇到比当前温度高的则停止，并记录相差的天数
 * 2）、遍历加栈存储
 * - 使用栈保存遍历的温度数据，当遍历到的温度比栈顶温度更高时，出栈操作，出栈后继续与栈顶元素遍历，直到栈顶元素更小或栈为空，则入栈操作
 * - 栈中保存的是温度的小标数据
 */
vector<int> dailyTemperatures(vector<int> &temperatures)
{
    int size = temperatures.size();
    std::stack<int> stack;
    std::vector<int> res(size, 0);

    for (int i = 0; i < size; i++)
    {
        int itemTemp = temperatures[i];
        if (stack.empty())
        {
            stack.push(i);
            continue;
        }

        while (!stack.empty())
        {
            int index = stack.top();
            int topTemp = temperatures[index]; // 栈顶温度
            if (itemTemp <= topTemp)           // 栈顶温度更大，遍历温度入栈
            {
                stack.push(i);
                break;
            }
            // 否则出栈,并计算天数差值
            stack.pop();
            res[index] = i - index;

            // 出栈后，栈为空，则直接入栈
            if (stack.empty())
            {
                stack.push(i);
                break;
            }
        }
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    // 89,62,70,58,47,47,46,76,100,70
    vector<int> temperatures = {89, 62, 70, 58, 47, 47, 46, 76, 100, 70};
    for (auto element : temperatures)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    auto res = dailyTemperatures(temperatures);
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
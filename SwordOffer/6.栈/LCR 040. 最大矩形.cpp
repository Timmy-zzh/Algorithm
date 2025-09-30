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
LCR 040. 最大矩形
https://leetcode.cn/problems/PLYXKQ/description/

给定一个由 0 和 1 组成的矩阵 matrix ，找出只包含 1 的最大矩形，并返回其面积。
注意：此题 matrix 输入格式为一维 01 字符串数组。

示例 1：
输入：matrix = ["10100","10111","11111","10010"]
输出：6
解释：最大矩形如上图所示。

示例 2：
输入：matrix = []
输出：0

示例 3：
输入：matrix = ["0"]
输出：0

示例 4：
输入：matrix = ["1"]
输出：1

示例 5：
输入：matrix = ["00"]
输出：0

提示：
rows == matrix.length
cols == matrix[0].length
0 <= row, cols <= 200
matrix[i][j] 为 '0' 或 '1'
 */

int largestRectangleArea(vector<int> &heights)
{
    std::stack<int> stack;
    stack.push(-1);
    int res = 0;

    // 遍历数组
    for (int i = 0; i < heights.size(); i++)
    {
        // 遍历元素与栈顶元素判断，遇到栈顶元素比遍历元素大的要进行出栈
        while (stack.top() != -1 && heights[stack.top()] >= heights[i])
        {
            int topI = stack.top();
            stack.pop();

            // 计算面积
            int area = heights[topI] * (i - stack.top() - 1);
            res = std::max(res, area);
        }
        // 并且最终遍历元素要入栈
        stack.push(i);
    }

    // 遍历完后，栈中还有元素，继续
    while (stack.top() != -1)
    {
        int topI = stack.top();
        stack.pop();

        // 计算面积
        int area = heights[topI] * (heights.size() - stack.top() - 1);
        res = std::max(res, area);
    }

    return res;
}

/**
 * 1、审题：输入一个只包含0和1的字符串组成的矩阵，求全部由1组成的矩形的最大面积
 * 2、解题：
 * - 该题可以转换为LCR 039题，将字符串矩阵转换为不同高度的直方图矩形，每个直方图的高度根据该位置上的字符串赋值，
 * -- 如果全是1，那高度是就是对应直方图的高度，如果中间出现0，则高度中断增加
 * - 根据获取拿到的每个直方图的高度，去求取矩形的最大面积
 */
int maximalRectangle(vector<string> &matrix)
{
    if (matrix.empty())
    {
        return 0;
    }
    std::vector<int> heights(matrix[0].length(), 0);
    int res = 0;
    for (std::string str : matrix)
    {
        // 求直方图的高度
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '0')
            {
                heights[i] = 0;
            }
            else
            {
                heights[i]++;
            }
        }
        res = std::max(res, largestRectangleArea(heights));
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    vector<string> matrix = {"10100", "10111", "11111", "10010"};

    for (auto ele : matrix)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    auto res = maximalRectangle(matrix);

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
    //     for (auto element : ele)
    //     {
    //         std::cout << element << ",";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}
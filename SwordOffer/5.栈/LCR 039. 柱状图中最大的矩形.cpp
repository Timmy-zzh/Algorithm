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
LCR 039. 柱状图中最大的矩形
https://leetcode.cn/problems/0ynMMM/description/

给定非负整数数组 heights ，数组中的数字用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

示例 1:
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10

示例 2：
输入： heights = [2,4]
输出： 4

提示：
1 <= heights.length <=105
0 <= heights[i] <= 104
 */

int realArea(int left, int right, vector<int> &heights)
{
    std::cout << "left:" << left << " ,right:" << right << std::endl;
    if (left >= heights.size())
    {
        return 0;
    }
    if (left >= right) // 区间范围只有一个
    {
        return heights[left];
    }

    // 找到该区间最小值，再分成三个部分，继续递归遍历
    int minI = left;
    for (int i = left; i <= right; i++)
    {
        if (heights[i] < heights[minI])
        {
            minI = i;
        }
    }
    int leftA = realArea(left, minI - 1, heights);
    int area = heights[minI] * (right - left + 1);
    int rightA = 0;
    if (minI < heights.size())
    {
        rightA = realArea(minI + 1, right, heights);
    }
    area = std::max(area, leftA);
    return std::max(area, rightA);
}

int largestRectangleArea2(vector<int> &heights)
{
    return realArea(0, heights.size() - 1, heights);
}

/**
 * 1、审题：输入一个int[]数组，元素值表示柱子的高度，现在要求這些柱子组成的矩形大小，求最大矩形面积并返回
 * 2、解题：
 * 1）暴力解法
 * - 两层for循环确定矩形的宽度，在这个宽度区间范围内查找高度最低的元素值，并求最终的矩形面积进行比较，最后返回最大矩形面积
 * 2）、分治法：
 * - 在数组元素内找到最小值，以最小元素值为基准将数组分为三个区间，分别求这三个区间的矩形面积，
 * - 左右两个区间可以继续拆分，直到区间范围为1个宽度
 * 3）、单调栈解法：
 * - 遍历矩形高度，使用栈保存柱子的下标位置，要求栈中的元素高度是递增的，
 * - 当遍历到的柱子比栈顶元素高时，柱子入栈
 * - 当遍历到的柱子比栈顶元素低时，则栈顶元素出栈，并且计算以该栈顶元素柱子为高度的矩形面积，因为栈中柱子时递增的。
 * -- 栈中前一个柱子的高度比栈顶柱子更低，而中间位置的柱子（如果存在）高度肯定是比栈顶元素柱子高，
 * -- 这样矩形的宽度就是当前栈顶元素的位置，到栈中前一个元素位置的距离，
 * - 栈中元素出栈后，得到以当前柱子为高度的矩形面积，栈中可能还存在比遍历元素高的柱子需要出栈，继续求以他为高度的矩形面积
 */
int largestRectangleArea1(vector<int> &heights)
{
    int res = 0;
    int count = heights.size();
    for (int i = 0; i < count; i++)
    {
        int minH = heights[i];
        for (int j = i; j < count; j++)
        {
            // 查找最小值
            if (heights[j] < minH)
            {
                minH = heights[j];
            }
            int area = minH * (j - i + 1);
            // std::cout << "i:" << i << " ,minH:" << minH << ",area:" << area << std::endl;
            res = std::max(res, area);
        }
    }
    return res;
}

/**
 * 单调栈解法
 * - 单调栈是要求在遍历数组元素的过程中，每一个遍历区间，单调栈中的元素都保持升序排序。
 * - 例如数组遍历过程中存在n个区间[0,0],[0,2]... [0,n-1] ,在這些区间过程中单调栈中的元素都保持升序
 * - 所以数组遍历过程中，需要判断遍历元素与栈顶元素的大小，如果遍历元素更大，则元素入栈，单调栈数据维持升序
 * -- 如果遍历元素更小，那要保证该区间范围内，单调栈的升序，那就需要将栈顶元素出栈，继续判断新的栈顶元素与遍历元素的大小，
 * -- 直至遍历元素更大(while循环)，然后执行入栈，这样能保证除了栈顶哪个元素比他小，中间区域比遍历元素大的数据都出栈了，此时遍历元素就是该中间区域的最小值
 * - 当栈顶元素出栈时，该元素是中间区域的最小值，以该元素为高度，并进行出栈，宽度为遍历元素位置和新的栈顶元素之间范围。进行求矩形面积
 * - 栈中元素保存的是数组元素的下标，为更方便计算中间区域的宽度，默认将-1位置入栈
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

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    vector<int> params = {2, 1, 5, 6, 2, 3};
    // vector<int> params = {2, 4};
    // vector<int> params = {4, 2};

    for (auto ele : params)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    auto res = largestRectangleArea(params);

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
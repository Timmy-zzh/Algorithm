#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
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
LCR 041. 数据流中的移动平均值
https://leetcode.cn/problems/qIsx9U/description/

给定一个整数数据流和一个窗口大小，根据该滑动窗口的大小，计算滑动窗口里所有数字的平均值。
实现 MovingAverage 类：
MovingAverage(int size) 用窗口大小 size 初始化对象。
double next(int val) 成员函数 next 每次调用的时候都会往滑动窗口增加一个整数，请计算并返回数据流中最后 size 个值的移动平均值，即滑动窗口里所有数字的平均值。

示例：
输入：
inputs = ["MovingAverage", "next", "next", "next", "next"]
inputs = [[3], [1], [10], [3], [5]]
输出：
[null, 1.0, 5.5, 4.66667, 6.0]

解释：
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // 返回 1.0 = 1 / 1
movingAverage.next(10); // 返回 5.5 = (1 + 10) / 2
movingAverage.next(3); // 返回 4.66667 = (1 + 10 + 3) / 3
movingAverage.next(5); // 返回 6.0 = (10 + 3 + 5) / 3

提示：
1 <= size <= 1000
-105 <= val <= 105
最多调用 next 方法 104 次
 *
 */

/**
 * 1、审题：
 * - 设置一个结构类，要求在一个固定长度的滑动窗口中，求窗口中所有数字的平均值
 * 2、解题：
 * - 类的构造函数参数，传入滑动窗口的大小，使用一个private属性进行持有
 * - 每次调用next方法，都会往窗口中插入一个数据，使用队列保存插入的数据，队列插入位置在尾部，
 * -- 当队列的元素超过滑动窗口的大小，则需要队列从队头删除元素
 * - 要求队列中元素的平均值，需要遍历其中的所有数据，并处于个数，需要耗费更多计算，可以使用一个sum变量保存滑动窗口中元素的和，并处于队列的大小即可
 */
class MovingAverage
{
public:
    MovingAverage(int size) : capacity(size), sum(0)
    {
    }

    double next(int val)
    {
        sum += val;
        queue.push(val);
        if (queue.size() > capacity)
        {
            sum -= queue.front(); // 队头数据出队列
            queue.pop();
        }
        return sum / queue.size();
    }

private:
    int capacity;          // 容量
    std::queue<int> queue; // 队列
    double sum;
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
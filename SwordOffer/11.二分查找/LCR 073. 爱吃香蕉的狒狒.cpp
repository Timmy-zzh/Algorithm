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

#include <random>
#include <algorithm>

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
LCR 073. 爱吃香蕉的狒狒
https://leetcode.cn/problems/nZZqjQ/description/

狒狒喜欢吃香蕉。这里有 N 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 H 小时后回来。
狒狒可以决定她吃香蕉的速度 K （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 K 根。
如果这堆香蕉少于 K 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉，下一个小时才会开始吃另一堆的香蕉。
狒狒喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
返回她可以在 H 小时内吃掉所有香蕉的最小速度 K（K 为整数）。

示例 1：
输入: piles = [3,6,7,11], H = 8
输出: 4

示例 2：
输入: piles = [30,11,23,4,20], H = 5
输出: 30

示例 3：
输入: piles = [30,11,23,4,20], H = 6
输出: 23

提示：
1 <= piles.length <= 10^4
piles.length <= H <= 10^9
1 <= piles[i] <= 10^9
 */

/**
 * 1、审题：
 * - 输入一个整数数组piles，数组的长度表示有length堆香蕉，数组元素值表示每堆香蕉的个数，h表示守卫离开的时间
 * - 现在猴子需要在守卫离开的时间内将所有香蕉吃完，且每堆香蕉吃完后的一小时内，不再吃东西，需要等待下一个小时才开始吃下一堆香蕉
 * - 要求猴子吃香蕉的最低速度k，猴子使用这个吃香蕉的速度要尽量慢，且能够在守卫离开的h时间内吃完
 * 2、解题：
 * - 二分查找法，查找猴子吃香蕉的最低速度，满足吃完所有香蕉的时间要在h时间内
 * - 找到香蕉数组中其中一堆数量最大的一个元素，作为猴子吃香蕉的最大速度maxSpeed，最小值为1，所以猴子的吃香蕉的速度范围值为[1,maxSpeed],
 * - 现在要在这个返回里面选择一个最小的吃香蕉速度，满足在h时间内将所有香蕉吃完
 * - 不断通过二分查找得到可变的吃香蕉速度currSpeed，并且计算以该速度来吃香蕉需要花费的总时间，使用该速度计算得到的总时间与h时间比较
 * - 如果总花费时间比h时间更大，不行，currSpeed速度太慢了，得加快吃香蕉的速度
 * - 如果总花费时间比h时间小，且更慢的速度（currSpeed-1）所花的时间比h时间大，则currSpeed速度为所求的最小吃香蕉速度
 */

// 计算以当前speed速度，吃完所有的香蕉，需要的总时间
int calcAllTimes(int speed, vector<int> &piles)
{
    int allTime = 0;
    // 计算没堆香蕉需要花费的时间，将所有时间累加返回
    for (auto pile : piles)
    {
        int time = pile / speed + (pile % speed == 0 ? 0 : 1);
        allTime += time;
    }
    return allTime;
}

int minEatingSpeed(vector<int> &piles, int h)
{
    int maxSpeed = 0;
    for (auto pile : piles)
    {
        maxSpeed = std::max(maxSpeed, pile);
    }
    int left = 1;
    int right = maxSpeed;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        std::cout << "left:" << left << " ,right:" << right << " ,mid:" << mid << std::endl;
        int time = calcAllTimes(mid, piles);
        std::cout << "time:" << time << std::endl;
        std::cout << std::endl;

        // if (time == h)
        // {
        //   return mid;
        // }

        if (time <= h)
        {
            if (mid == 1 || calcAllTimes(mid - 1, piles) > h)
            {
                return mid;
            }
            right = mid - 1;
        }
        else
        {
            // 时间太多了，速度太慢了，需要加快速度
            left = mid + 1;
        }
    }
    return maxSpeed;
}

int main()
{
    std::cout << "《C++ Primer Plus》" << std::endl;

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
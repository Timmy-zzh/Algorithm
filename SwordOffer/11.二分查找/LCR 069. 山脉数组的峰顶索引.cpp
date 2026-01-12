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
LCR 069. 山脉数组的峰顶索引
https://leetcode.cn/problems/B1IidL/description/

符合下列属性的数组 arr 称为 山峰数组（山脉数组） ：
arr.length >= 3
存在 i（0 < i < arr.length - 1）使得：
arr[0] < arr[1] < ... arr[i-1] < arr[i]
arr[i] > arr[i+1] > ... > arr[arr.length - 1]
给定由整数组成的山峰数组 arr ，返回任何满足 arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1] 的下标 i ，即山峰顶部。

示例 1：
输入：arr = [0,1,0]
输出：1

示例 2：
输入：arr = [1,3,5,4,2]
输出：2

示例 3：
输入：arr = [0,10,5,2]
输出：1

示例 4：
输入：arr = [3,4,5,1]
输出：2

示例 5：
输入：arr = [24,69,100,99,79,78,67,36,26,19]
输出：2

提示：
3 <= arr.length <= 104
0 <= arr[i] <= 106
题目数据保证 arr 是一个山脉数组

进阶：很容易想到时间复杂度 O(n) 的解决方案，你可以设计一个 O(log(n)) 的解决方案吗？
 */

/**
 * 1、审题：输入一个山峰数组，就是数据前半部分排序不断升高，后半部分不断降低，要求找出这个山峰的封顶位置
 * 2、解题：
 * - 普通解法：遍历整个数组元素，峰顶元素肯定是比前后两个元素都大的数据，需要O(n)算法复杂度
 * - 二分查找解法：使用两个指针left，right标记数组的前后两个元素位置，不断计算得出中间元素位置mid
 * - 如果mid下标元素，比前后两个元素都大，则命中
 * - 如果mid下标元素，比前一个元素大，处于升序部分，则峰顶元素在数组后半部分，反之峰顶元素在前半部分
 * - 山峰数组最后有三个元素组成，left与right可以从第二个位置元素开始遍历查找
 */
int peakIndexInMountainArray(vector<int> &arr)
{
    int left = 1;
    int right = arr.size() - 2;
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1])
        {
            return mid;
        }
        // 升序部分
        if (arr[mid - 1] < arr[mid])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

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
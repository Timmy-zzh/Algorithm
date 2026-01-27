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
 * - 脑子得练才行，光看书，不动手写，那不行！效果打/home/yingzi/zzh_work/github/Algorithm/SwordOffer/12.排序/LCR 075. 数组的相对排序.cpp骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
 LCR 076. 数组中的第 K 个最大元素
 https://leetcode.cn/problems/xx4gT2/description/

给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1：
输入：nums = [3,2,1,5,6,4], k = 2
输出：5

示例 2：
输入：nums = [3,2,3,1,2,4,5,5,6], k = 4
输出：4

提示：
1 <= k <= nums.length <= 104
-104 <= nums[i] <= 104
 */

/**
 * 1、审题：
 * - 输入一个数组和数字k，要求找到数组中第k个大的数字并返回
 * 2、解题：
 * - 最小堆解法：创建一个包含k个元素的最小堆，遍历数组，当元素大于堆顶元素时，堆顶元素出栈，然后插入遍历元素，最后返回堆顶元素
 * - 分治法：采用快速排序查找基准值的方式，不断求基准值，判断基准值位置与第k大元素的顺序，如果基准值刚好等于第k-1位置，直接返回
 * - 否则不断从前后两个区域继续求取基准值下标位置
 */

static int getRandom(int start, int end)
{
    if (start >= end)
    {
        return start;
    }
    std::random_device rd;
    std::mt19937 gen(rd()); // 随机因子吗？

    // 定义分布范围
    std::uniform_int_distribution<> dis(start, end - 1);

    int random_num = dis(gen);
    return random_num;
}

// 数组元素交换
void mySwap(std::vector<int> &nums, int a, int b)
{
    int temp = nums[a];
    nums[a] = nums[b];
    nums[b] = temp;
}

/**
 * 求数组的基准值
 * - 先获取[start,end]范围中间的一个随机数
 * - 以该位置为基准厨师下标索引位置，将数组分为两个区域，前面的区域的值都小于基准值，后面的区域范围值都大于基准值
 * - 遍历区域范围元素，使用一个small标记记录，当前小于基准值的下标，在遍历过程中，当遇到比基准值小的元素，
 * - 将small后面的大于基准值的元素和遍历到的小元素进行交换
 */
int getPovit(std::vector<int> &nums, int start, int end)
{
    // 获取一个随机数，取值范围[start,end]
    int randomIndex = getRandom(start, end);
    mySwap(nums, randomIndex, end);

    int small = start - 1;
    for (int i = start; i < end; i++)
    {
        if (nums[i] < nums[end])
        {
            small++;
            mySwap(nums, small, i);
        }
    }

    small++;
    mySwap(nums, small, end);
    return small;
}

int findKthLargest(vector<int> &nums, int k)
{
    int left = 0;
    int right = nums.size() - 1;
    int targetIndex = nums.size() - k;
    int povit = getPovit(nums, left, right);

    while (povit != targetIndex)
    {
        if (povit < targetIndex)
        {
            left = povit + 1;
        }
        else
        {
            right = povit - 1;
        }
        povit = getPovit(nums, left, right);
    }
    return nums[povit];
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
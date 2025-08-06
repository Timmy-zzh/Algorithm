#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
using namespace std;

/**
给定一个整数数组和一个整数 k ，请找到该数组中和为 k 的连续子数组的个数。

示例 1：
输入:nums = [1,1,1], k = 2
输出: 2
解释: 此题 [1,1] 与 [1,1] 为两种不同的情况

示例 2：
输入:nums = [1,2,3], k = 3
输出: 2
 */

/**
 * 数组累加法：
 * - 将数组中所有元素的值累加起来，使用哈希表保存子数组累加和出现的次数
 * 例子：有数组 {1，2，3，4，5，6} 加入要求子数组和为9的子数组出现的个数
 * 可以通过累加计算得到前三个数组元素的累加和 S3 = 1+2+3 = 6
 * 前5个数组元素累加和为 S5 = 1+2+3+4+5 = 15；
 * 那子数组和为9 = S5 - S3；可通过计算累加相减是否等于目标值来求符合条件的子数组
 * = 该方法有点类似动态规划解法
 */
int subarraySum(vector<int> &nums, int k)
{
    int res = 0;
    // std::map<int, int> sumCountMap{{0, 1}}; // 初始化
    std::map<int, int> sumCountMap;
    // 往map中插入元素
    sumCountMap[0] = 1;
    // sumCountMap.insert({0, 1});

    int sum = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];

        // 判断是否存在 sum-k的key值
        if (sumCountMap.find(sum - k) != sumCountMap.end())
        {
            res += sumCountMap.at(sum - k);
        }

        // 在往map中插入累加值
        int count = 0;
        if (sumCountMap.find(sum) != sumCountMap.end())
        {
            count = sumCountMap.at(sum);
        }
        sumCountMap[sum] = count + 1;
    }

    return res;
}

/**
 * 解法2：双指针解法
 * - 没法弄，right指针右移了，可能需要左指针左移，
 * - 双指针解法只能都往右移
 */
int subarraySum2(vector<int> &nums, int k)
{
    int res = 0;

    return res;
}

/**
 * 1、审题：
 * - 输入一个整数数组和一个整数值k，要求从整数数组中找出存在的子数组个数，要求子数组的和等于k
 * 2、解题：
 * 暴力解法：
 * - 双层for循环，外层for循环定位子数组的开始位置，内层for循环定义子数组的结束位置，
 * - 在内层for循环中，将子数组所有的元素相加，判断结果累加结果sum是否等于目标值k，如果等于则找到符合要求的子数组
 * - 结果值+1
 */
int subarraySum1(vector<int> &nums, int k)
{
    int res = 0;
    int size = nums.size();
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = 0;
        for (int j = i; j < size; j++)
        {
            sum += nums[j];
            if (k == sum)
            {
                res++;
            }
        }
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    // vector<int> nums = {1, 1, 1};

    vector<int> nums = {1, -1, 0};
    auto res = subarraySum(nums, 0);

    std::cout << "res:" << res << std::endl;

    // 遍历数组1
    // for (int element : res)
    // {
    //     std::cout << element << ",";
    // }
    // std::cout << std::endl;

    // 遍历数组2
    // for (vector<int> ele : res)
    // {
    //     for (int element : ele)
    //     {
    //         std::cout << element << ",";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}
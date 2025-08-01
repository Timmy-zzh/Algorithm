#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
using namespace std;

/**
给定一个正整数数组 nums和整数 k ，请找出该数组内乘积小于 k 的连续的子数组的个数。

示例 1：
输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8 个乘积小于 100 的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于100的子数组。

示例 2：
输入: nums = [1,2,3], k = 0
输出: 0
 */

/**
 * 1、审题
 * - 输入一个整数数组，和整数k，要求在数组中找出子数组的个数，要求子数组的元素乘积要小于整数k
 * 2、解题：双指针解法，和lcr8题一样的思路
 * - 定义两个指针left，right，刚开始两个指针的都在数组小标0的位置，判断他们的乘积，
 * - 如果乘积大于目标值k，则左侧指针left右移，并将乘积除于左指针位置的元素，
 * - 当乘积小于目标值k，计算当前子数组
 */
int numSubarrayProductLessThanK(vector<int> &nums, int k)
{
    int res = 0;
    int product = 1; // 子数组的乘积
    int left = 0;
    for (int right = 0; right < nums.size(); right++)
    {
        product *= nums[right];
        while (left <= right && k <= product)
        {
            product /= nums[left++];
        }
        res += (left <= right) ? (right - left + 1) : 0;
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    vector<int> nums = {10, 5, 2, 6};
    auto res = numSubarrayProductLessThanK(nums, 100);

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
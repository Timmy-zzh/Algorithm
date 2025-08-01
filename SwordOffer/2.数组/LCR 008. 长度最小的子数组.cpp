#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
using namespace std;

/**
给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，
并返回其长度。如果不存在符合条件的子数组，返回 0 。

示例 1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。

示例 2：
输入：target = 4, nums = [1,4,4]
输出：1

示例 3：
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
 */

/**
 * 1、审题
 * - 输入一个整数数组和一个目标值k，要求从数组中找出一个最短的子数组，其和要求大于等于k，返回最短子数组的长度
 * 2、解题
 * 双指针解法，指针同向
 * - 设置两个指针left，和right，刚开始都在数组下标0位置，判断子数组的和是否大于目标值k，
 * - 如果和大于等于目标值，则左指针left右移，否则右指针right右移
 */
int minSubArrayLen(int target, vector<int> &nums)
{
    if (nums.size() == 0)
    {
        return 0;
    }
    int res = INT32_MAX;
    int sum = 0; // 计算子数组的和
    int left = 0;
    int right = 0;

    for (; right < nums.size(); right++)
    {
        sum += nums[right];
        while (target <= sum && left <= right)
        {
            res = std::min(res, right - left + 1);
            // std::cout << "left:" << left << " ,right:" << right << " ,res:" << res << std::endl;
            sum -= nums[left];
            left++;
        }
    }

    return res == INT32_MAX ? 0 : res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    auto res = minSubArrayLen(7, nums);

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
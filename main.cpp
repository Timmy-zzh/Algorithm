#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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

int subarraySum(vector<int> &nums, int k)
{

    return 0;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    vector<int> nums = {1, 1, 1};
    auto res = subarraySum(nums, 2);

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
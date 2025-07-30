#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
using namespace std;

/**
 * LCR 007. 三数之和
 * https://leetcode.cn/problems/1fGaJU/description/
 *
 * 给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a ，b ，c ，
 * 使得 a + b + c = 0 ？请找出所有和为 0 且 不重复 的三元组。

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]

示例 2：
输入：nums = []
输出：[]

示例 3：
输入：nums = [0]
输出：[]
 */

/**
 * 1、审题：输入一个整数数组，要求找出数组中三个元素，要求三个元素的和为0，三个元素的组合存在多个，返回所有的组合
 * 2、解题：
 * 暴力解法：三层for循环，时间复杂度为n的三次方
 * 先排序，后查找两数之和，数组排序时间复杂度为nlogn，查找两数之和采用双指针解法时间复杂度为n，
 * - 为了避免重复，在遍历过程中，遇到和前一个相同的元素，需要进行过滤
 * - 整体时间复杂度为n*logn + n^2
 */
vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> res;

    // 对数组进行排序
    std::sort(nums.begin(), nums.end());
    for (auto num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < nums.size(); i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }

        int left = i + 1;
        int right = nums.size() - 1;
        while (left < right)
        {
            if ((nums[i] + nums[left] + nums[right]) == 0)
            {
                res.push_back({nums[i], nums[left], nums[right]});
                left++;
                // 判断是否遇到相同的元素，需要进行过滤
                while (nums[left] == nums[left - 1] && left < right)
                {
                    left++;
                }
            }
            else if ((nums[left] + nums[right]) < -nums[i])
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    // vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<int> nums = {0, 0, 0, 0};
    // vector<int> nums = {-1, 0, 1, 0};

    auto res = threeSum(nums);

    // std::cout << "res:" << res << std::endl;

    // 遍历res
    for (vector<int> ele : res)
    {
        for (int element : ele)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
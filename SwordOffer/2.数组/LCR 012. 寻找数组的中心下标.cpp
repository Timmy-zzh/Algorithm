#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 */
using namespace std;
using namespace std;

/**
给你一个整数数组 nums ，请计算数组的 中心下标 。
数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。
如果中心下标位于数组最左端，那么左侧数之和视为 0 ，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。
如果数组有多个中心下标，应该返回 最靠近左边 的那一个。如果数组不存在中心下标，返回 -1 。

示例 1：
输入：nums = [1,7,3,6,5,6]
输出：3
解释：
中心下标是 3 。
左侧数之和 sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11 ，
右侧数之和 sum = nums[4] + nums[5] = 5 + 6 = 11 ，二者相等。

示例 2：
输入：nums = [1, 2, 3]
输出：-1
解释：
数组中不存在满足此条件的中心下标。

示例 3：
输入：nums = [2, 1, -1]
输出：0
解释：
中心下标是 0 。
左侧数之和 sum = 0 ，（下标 0 左侧不存在元素），
右侧数之和 sum = nums[1] + nums[2] = 1 + -1 = 0 。
 */

/**
 * 1、审题：
 * 输入一个数组，需要找出数组中的一个元素，要求该元素位置左边区域的子数组累加和，等于该元素位置右边区域子数组的累加和
 * 2、解题
 * - 将数组所有元素累加，
 * - 再遍历数组，得到子数组的累加和，判断遍历元素的左右区域子数组的累积和是否相同，相同则返回该元素下标
 */
int pivotIndex(vector<int> &nums)
{
    int res = -1;
    int total = 0;
    int sum = 0;
    for (int num : nums)
    {
        total += num;
    }
    for (int i = 0; i < nums.size(); i++)
    {
        if (sum == (total - sum - nums[i]))
        {
            return i;
        }
        sum += nums[i];
    }
    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    vector<int> nums = {1, 7, 3, 6, 5, 6};
    // vector<int> nums = {0, 1, 0};

    for (int element : nums)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    auto res = pivotIndex(nums);

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
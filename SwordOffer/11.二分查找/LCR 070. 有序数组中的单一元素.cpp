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
LCR 070. 有序数组中的单一元素
https://leetcode.cn/problems/skFtm2/description/

给定一个只包含整数的有序数组 nums ，每个元素都会出现两次，唯有一个数只会出现一次，请找出这个唯一的数字。

示例 1：
输入: nums = [1,1,2,3,3,4,4,8,8]
输出: 2

示例 2：
输入: nums =  [3,3,7,7,10,11,11]
输出: 10

提示：
1 <= nums.length <= 105
0 <= nums[i] <= 105
进阶：采用的方案可以在 O(log n) 时间复杂度和 O(1) 空间复杂度中运行吗？
 */

/**
 * 解法2：二分查找解法
 * - 使用异或操作的解法时间复杂度为O(n),没有使用有序数组的特性
 * - 将数组元素从最开始位置，两两合在一起判断，查找其中的两个元素是否相等，如果相同则不同的元素在后面
 * - 如果不同，需要判断是否是第一组不相同的数组组合，如果不是则继续遍历前面的组合，前面的数组组合刚好两个元素相同则命中。
 */
int singleNonDuplicate(vector<int> &nums)
{
    int res = nums[0];
    int left = 0;
    int right = nums.size() - 1;
    if (right == 0)
    {
        return res;
    }
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        mid = (mid / 2) * 2;

        if (mid == 0 && nums[mid] != nums[mid + 1])
        {
            return nums[mid];
        }
        if (nums[mid] != nums[mid + 1] && nums[mid - 2] == nums[mid - 1])
        {
            return nums[mid];
        }
        if (nums[mid] == nums[mid + 1])
        {
            left = mid + 2;
        }
        else
        {
            right = mid - 2;
        }
    }
    return res;
}

/**
 * 1、审题：
 * - 输入一个排序好的数组，其中的每个元素都会重复出现两次，只有一个元素只单独出现一次，找出这个元素并返回
 * 2、解题：
 * - 使用异或进位解法，将所有的元素进行两两xor异或计算，最后得到的就是结果
 * - 异或操作，是相同的位最后结果为0
 */
int singleNonDuplicate1(vector<int> &nums)
{
    int res = 0;
    for (const auto num : nums)
    {
        res ^= num;
    }
    return res;
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
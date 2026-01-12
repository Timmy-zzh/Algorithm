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
LCR 068. 搜索插入位置
https://leetcode.cn/problems/N6YdxV/description/

给定一个排序的整数数组 nums 和一个整数目标值 target ，请在数组中找到 target ，并返回其下标。如果目标值不存在于数组中，
返回它将会被按顺序插入的位置。请必须使用时间复杂度为 O(log n) 的算法。

示例 1：
输入: nums = [1,3,5,6], target = 5
输出: 2

示例 2：
输入: nums = [1,3,5,6], target = 2
输出: 1

示例 3：
输入: nums = [1,3,5,6], target = 7
输出: 4

示例 4：
输入: nums = [1,3,5,6], target = 0
输出: 0

示例 5：
输入: nums = [1], target = 0
输出: 0

提示：
1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 为无重复元素的升序排列数组
-104 <= target <= 104
 */

/**
 * 1、审题：
 * - 输入一个升序排序的整数数组和一个目标值target，要求在数组中查找是否存在目标值，如果存在返回该目标值在数组中的下标位置，
 * -- 如果不存在，返回插入该数值应该所在的位置
 * 2、解题：题目要求使用二分查找法
 * - 使用左右指针left，right分别标记查找范围，取中间值mid
 * - 如果mid下标值等于目标值，则返回mid
 * - 如果mid值大于目标值，且mid-1小于目标值，则查找到插入位置，如果mid已经是小标0了，也直接返回
 * - 如果mid值小于目标值，继续在后半部分查找， left = mid + 1
 * - 如果还是没有找到，说明数组中所有元素都大小目标值，应该插入到数组最末尾端
 */
int searchInsert(vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    int mid = 0;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            return mid;
        }

        if (nums[mid] > target)
        {
            if (mid == 0 || nums[mid - 1] < target)
            {
                return mid;
            }
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return nums.size();
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
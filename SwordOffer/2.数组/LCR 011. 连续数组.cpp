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
给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。

示例 1：
输入: nums = [0,1]
输出: 2
解释: [0, 1] 是具有相同数量 0 和 1 的最长连续子数组。

示例 2：
输入: nums = [0,1,0]
输出: 2
解释: [0, 1] (或 [1, 0]) 是具有相同数量 0 和 1 的最长连续子数组。
 */

/**
 * 1、审题：
 * 输入一个数组，找到一个子数组，要求子数组中0和1的个数相同，返回最长子数组的长度
 * 2、解题：累加和解法
 * - 要求子数组中0和1的个数相同，可以变换一下，将子数组中的0变成-1进行累加计算，这样问题变为求累积和为0的子数组
 * - 和LCR10题类似的思路，将子数组的累加和和当前子数组的位置使用哈希表保存下来，在后面的子数组累加和中，判断哈希表是否存在相同的累加和
 * - 如果相同，则说明中间位置的子数组累加和等于0，该子数组长度即为目标子数组
 */
int findMaxLength(vector<int> &nums)
{
    int res = INT32_MIN;
    std::map<int, int> sumIndexMap;
    sumIndexMap.insert({0, -1});
    int sum = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        sum += (nums[i] == 0 ? -1 : nums[i]);
        if (sumIndexMap.find(sum) != sumIndexMap.end())
        { // 存在目标累加和sum
            int index = sumIndexMap.at(sum);
            res = max(res, (i - index));
        }
        else
        {
            sumIndexMap[sum] = i;
        }
    }

    return res == INT32_MIN ? 0 : res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    vector<int> nums = {0, 1, 0, 1};
    // vector<int> nums = {0, 1, 0};
    auto res = findMaxLength(nums);

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
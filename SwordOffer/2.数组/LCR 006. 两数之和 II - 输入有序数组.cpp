#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

/**
给定一个已按照 升序排列  的整数数组 numbers ，请你从数组中找出两个数满足相加之和等于目标数 target 。
函数应该以长度为 2 的整数数组的形式返回这两个数的下标值。numbers 的下标 从 0 开始计数 ，
所以答案数组应当满足 0 <= answer[0] < answer[1] < numbers.length 。
假设数组中存在且只存在一对符合条件的数字，同时一个数字不能使用两次。

示例 1：
输入：numbers = [1,2,4,6,10], target = 8
输出：[1,3]
解释：2 与 6 之和等于目标数 8 。因此 index1 = 1, index2 = 3 。

示例 2：
输入：numbers = [2,3,4], target = 6
输出：[0,2]

示例 3：
输入：numbers = [-1,0], target = -1
输出：[0,1]
 */

/**
 * 双指针解法
 */
vector<int> twoSum2(vector<int> &numbers, int target)
{
    vector<int> res;
    int left = 0;
    int right = numbers.size() - 1;
    while (left < right && target != (numbers[left] + numbers[right]))
    {
        if (numbers[left] + numbers[right] < target)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    res.push_back(left);
    res.push_back(right);

    return res;
}

// 代码优化
vector<int> twoSum(vector<int> &numbers, int target)
{
    int left = 0;
    int right = numbers.size() - 1;
    while (left < right)
    {
        if (target == (numbers[left] + numbers[right]))
        {
            return {left, right};
        }
        if (numbers[left] + numbers[right] < target)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    return {-1, -1};
}

/**
 * 1、审题
 * - 输入一个整数数组和一个目标整数，要求从数组中找出两个数，要求他们的和等于目标整数，返回两个元素的下标数组
 * 2、解题：
 * 2.1、暴力解法：双层for循环，遍历数组获得整数元素，然后遍历其他元素，判断他们的和是否等于目标值
 * - 时间复杂度n的平方，没有使用到数组元素是升序排序的特性
 * 2.2、哈希表解法
 * - 遍历数组元素，遍历的过程中，判断目标值与遍历元素的差值，判断差值是否在哈希表中，如果存在则返回下标数组
 * - 如果不存在，则将当前遍历的元素和下标值，保存到哈希表中
 * 2.3、双指针解法
 * - 定义两个下标，从数组的两端开始往中间遍历
 * - 如果遍历到的两个元素的和等于目标值，则直接返回，如果两元素和大于目标值，则right角标左移，否则left角标右移
 */
vector<int> twoSum1(vector<int> &numbers, int target)
{
    vector<int> res;
    std::map<int, int> map;
    for (int i = 0; i < numbers.size(); i++)
    {
        int num = target - numbers[i];
        if (map.find(num) != map.end()) // 存在，取出下标值
        {
            res.push_back(map[num]);
            res.push_back(i);
            break;
        }
        map[numbers[i]] = i;
    }
    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    vector<int> numbers = {1, 2, 4, 6, 10};
    auto res = twoSum(numbers, 8);

    // std::cout << "res:" << res << std::endl;

    // 遍历res
    for (int element : res)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    return 0;
}
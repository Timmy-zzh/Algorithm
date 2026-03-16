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
#include "src/bean.h"

#include <random>
#include <algorithm>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LCR 079. 子集
https://leetcode.cn/problems/TVdhkn/description/

给定一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

示例 1：
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

示例 2：
输入：nums = [0]
输出：[[],[0]]

提示：
1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums 中的所有元素 互不相同
 */

void helper(vector<int> &nums, int index, vector<int> &list, vector<vector<int>> &result)
{
    // 遍历到数组最后一个元素了，结束，将单签子集list添加到结果中
    if (index == nums.size())
    {
        result.push_back(list);
        return;
    }

    // 当前遍历到的元素，有两种选择情况
    helper(nums, index + 1, list, result);

    // 子集添加当前元素
    list.push_back(nums[index]);
    helper(nums, index + 1, list, result);
    // 回到父节点，添加的元需要删除
    list.pop_back();
}

/**
 * 1、审题：输入一个整数数组，数组中的元素都不相同，现在要求这个数组所有的子集情况
 * - 要求子集中不能包含重复的子集，不考虑元素的排列顺序，意思是两个子集比较后不能包含相同的元素
 * - 空的子集也是所求
 * 2、解题：回溯算法
 * - 遍历原始数组，对于遍历到的元素，有两种选择方式，一种是放入到子集中，一种是不放入
 * - 可以类比为二叉树的情况，每个元素对于的不同选择方式，对应二叉树的情况
 * - 采用递归方式实现回溯算法
 */
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> result;
    if (nums.empty())
    {
        return result;
    }

    vector<int> list;
    helper(nums, 0, list, result);
    return result;
}

int main()
{
    std::cout << "《剑指offer》" << std::endl;
    ListNode node1(4);
    ListNode node2(2);
    ListNode node3(1);
    ListNode node4(3);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node1.print();

    // auto res = sortArray(nums);
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
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
LCR 084. 全排列 II
https://leetcode.cn/problems/7p8L0Z/description/

给定一个可包含重复数字的整数集合 nums ，按任意顺序 返回它所有不重复的全排列。

示例 1：
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]

示例 2：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

提示：
1 <= nums.length <= 8
-10 <= nums[i] <= 10
 */

/**
 * 1、审题：
 * - 输入一个数组，数组中的元素可能存在重复的元素，现在要找出该数组中所有存在的且不同的队列
 * 2、解题，回溯法
 * - 因为数组中存在相同的元素，按照83题的逻辑，已经将一个元素添加到队列中，这个位置还可以选择剩下的n-1个元素进行替换
 * - 如果元素值相同则，没有必要继续替换了，因为替换后生成的队列结果是一样的，所以需要过滤掉这种情况
 */
void swapEle(vector<int> &nums, int i, int j) // 数组元素交换
{
    if (i != j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}

void helper(vector<int> &nums, int index, vector<vector<int>> &res)
{
    if (index == nums.size())
    {
        res.push_back(nums);
        return;
    }

    vector<int> set;

    for (int i = index; i < nums.size(); i++)
    {
        if (std::find(set.begin(), set.end(), nums[i]) == set.end()) // 当前遍历的元素在set集合中不存在，则添加到队列中
        {
            set.push_back(nums[i]);

            swapEle(nums, i, index);

            helper(nums, index + 1, res);

            swapEle(nums, i, index);
        }
    }
}

vector<vector<int>> permuteUnique(vector<int> &nums)
{
    vector<vector<int>> res;

    helper(nums, 0, res);

    return res;
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
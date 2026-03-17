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
LCR 082. 组合总和 II
https://leetcode.cn/problems/4sjJUc/description/

给定一个可能有重复数字的整数数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次，解集不能包含重复的组合。

示例 1：
输入：candidates = [10,1,2,7,6,1,5], target = 8
输出：
[
  [1,1,6],
  [1,2,5],
  [1,7],
  [2,6]
]

示例 2：
输入：candidates = [2,5,2,1,2], target = 5
输出：
[
  [1,2,2],
  [5]
]

提示：
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
 */

/**
 * 1、审题：输入一个包含重复元素的数组，和一个目标int值target，要求从数组中找出和为target值的所有子集，并返回
 * - 要求子集中的元素不能重复相同，不考虑子集中元素的顺序
 * 2、解题：
 * - 先对数组元素进行排序处理， 使相同的元素排列在一块，后面有用到
 * - 使用递归函数不断选取数组中的元素进行处理，用target变量减去选中的元素值，直到target值小于等于0
 * - 本题中数组元素不能重复使用，但是数组中的元素存在相同的情况，所以在选取的时候有两种处理方式
 * - 一种是选中当前元素，或者不选当前元素并且后面相同的元素也不选中
 * 3、总结：
 * - 数组中存在相同元素的情况，要先排序后处理
 * - 求数组元素的子集的和等于目标值target，将选中的元素减去target，直到target目标值等于0
 * - 回溯法对于选中的元素，可以选中也可以不选中
 * - 当target等于0时，递归终止，其他已知道不符合结果的情况也可以修剪终止处理
 */

/**
 * 找到与index位置相同的元素，过滤，直到不相同的元素位置返回
 */
int getNext(vector<int> &candidates, int index)
{
    int next = index;
    while (next < candidates.size() && candidates[index] == candidates[next])
    {
        next++;
    }

    return next;
}

void helper(vector<int> &candidates, int target, int index, vector<int> &itemList, vector<vector<int>> &res)
{
    std::cout << "index:" << index << " ,target:" << target << std::endl;
    for (auto ele : itemList)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    if (target == 0)
    {
        res.push_back(itemList);
        return;
    }
    if (target < 0 || index >= candidates.size())
    {
        return;
    }

    // 不选择index该元素，并且后面相同元素也不选择
    int next = getNext(candidates, index);
    std::cout << "------ next:" << next << std::endl;
    helper(candidates, target, next, itemList, res);

    // 选择当前元素放入集合中
    itemList.push_back(candidates[index]);
    helper(candidates, target - candidates[index], index + 1, itemList, res);
    itemList.pop_back();
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    // 对数组元素进行排序
    std::sort(candidates.begin(), candidates.end());
    std::cout << "sort 11111 :" << std::endl;
    for (auto ele : candidates)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    //
    vector<vector<int>> res;
    vector<int> itemList;
    helper(candidates, target, 0, itemList, res);
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
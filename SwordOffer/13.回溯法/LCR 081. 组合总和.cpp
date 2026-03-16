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
LCR 081. 组合总和
https://leetcode.cn/problems/Ygoe9J/description/

给定一个无重复元素的正整数数组 candidates 和一个正整数 target ，找出 candidates 中所有可以使数字和为目标数 target 的唯一组合。
candidates 中的数字可以无限制重复被选取。如果至少一个所选数字数量不同，则两种组合是不同的。
对于给定的输入，保证和为 target 的唯一组合数少于 150 个。

示例 1：
输入: candidates = [2,3,6,7], target = 7
输出: [[7],[2,2,3]]

示例 2：
输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]

示例 3：
输入: candidates = [2], target = 1
输出: []

示例 4：
输入: candidates = [1], target = 1
输出: [[1]]

示例 5：
输入: candidates = [1], target = 2
输出: [[1,1]]

提示：
1 <= candidates.length <= 30
1 <= candidates[i] <= 200
candidate 中的每个元素都是独一无二的。
1 <= target <= 500
 */

/**
 * target采用减法，不断减去当前选中的元素i
 * target = 0时，表示找到了目标子集
 * 注意参数要使用引用数据
 */
void helper(vector<int> &candidates, int target, int index, vector<int> &item, vector<vector<int>> &res)
{
  if (target == 0)
  {
    res.push_back(item);
    return;
  }
  if (target < 0 || index >= candidates.size())
  {
    return;
  }

  // 遍历数组，对数组元素进行处理
  // 不对index数组元素进行选中
  helper(candidates, target, index + 1, item, res);

  item.push_back(candidates[index]);
  helper(candidates, target - candidates[index], index, item, res); // 选中，index不变，下次还可以选中
  item.pop_back();
}

/**
 * 1、审题：输入一个整数数组和一个整数目标值，要求从数组中选取多个元素组成子集，子集总和为target，可以重复从数组中选择元素
 * 2、解题：还是使用回溯法
 * - 每次都遍历数组元素，每个元素都面临不同的选择
 * - 当子集的和等于target目标值时，添加到结果中，如果子集的和大于目标值了，则停止递归遍历
 */
vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
  vector<vector<int>> res;
  vector<int> item;

  helper(candidates, target, 0, item, res);
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
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <queue>
#include "src/bean.h"

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
LCR 060. 前 K 个高频元素
https://leetcode.cn/problems/g5c51o/description/

给定一个整数数组 nums 和一个整数 k ，请返回其中出现频率前 k 高的元素。可以按 任意顺序 返回答案。

示例 1：
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2：
输入: nums = [1], k = 1
输出: [1]

提示：
1 <= nums.length <= 105
k 的取值范围是 [1, 数组中不相同的元素的个数]
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
进阶：所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。
 */

/**
 * 1、审题：
 * - 输入一个数组和k值，要求从数组中找出出现相同的数字，并且出现的次数排列在前k个的元素，并返回数组
 * 2、解题：
 * - 要求数字出现的次数，需要使用哈希表map保存每个数字，和其对应出现的次数
 * - 要求数字出现的最多的k次数，可以使用最小堆来比较元素出现的次数，次数比堆顶元素大的，则删除堆顶元素，并加入到最小堆中。如果比堆顶元素还小的，则直接过滤掉
 * - 最后将最小堆中的元素添加到集合中返回
 */

static bool camp(std::pair<int, int> &m, std::pair<int, int> &n)
{
  return m.second > n.second;
}

vector<int> topKFrequent(vector<int> &nums, int k)
{
  std::map<int, int> map;
  // 将数组元素添加到map哈希表中
  for (auto num : nums)
  {
    if (map.find(num) != map.end())
    {
      // 存在
      map[num]++;
    }
    else
    {
      map[num] = 1;
    }
  }

  // 最小堆,需要保存键值对，使用pair作为堆中存储的元素
  priority_queue<pair<int, int>, std::vector<pair<int, int>>, decltype(&camp)> min_heap(camp);
  // 遍历哈希表map
  for (auto mapItem : map)
  {
    if (min_heap.size() < k)
    {
      min_heap.emplace(mapItem.first, mapItem.second);
    }
    else
    {
      // 比较最小堆的堆顶元素
      if (min_heap.top().second < mapItem.second)
      {
        min_heap.pop();
        min_heap.emplace(mapItem.first, mapItem.second);
      }
    }
  }

  vector<int> res;
  while (!min_heap.empty())
  {
    res.push_back(min_heap.top().first);
    min_heap.pop();
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
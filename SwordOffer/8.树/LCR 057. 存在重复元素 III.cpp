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
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/**
LCR 057. 存在重复元素 III
https://leetcode.cn/problems/7WqeDu/description/

给你一个整数数组 nums 和两个整数 k 和 t 。请你判断是否存在 两个不同下标 i 和 j，使得 abs(nums[i] - nums[j]) <= t ，同时又满足 abs(i - j) <= k 。
如果存在则返回 true，不存在返回 false。

示例 1：
输入：nums = [1,2,3,1], k = 3, t = 0
输出：true

示例 2：
输入：nums = [1,0,1,1], k = 1, t = 2
输出：true

示例 3：
输入：nums = [1,5,9,1,5,9], k = 2, t = 3
输出：false

提示：
0 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1
0 <= k <= 104
0 <= t <= 231 - 1
 */
bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
{
  std::set<int> set;

  int count = nums.size();
  for (int i = 0; i < count; i++)
  {
    // 小于nums[i]的最大值
    auto it = set.lower_bound(nums[i]);
    if (it != set.begin())
    {
      it--;
      if ((static_cast<long>(nums[i]) - static_cast<long>(*it)) <= t)
        return true;
    }

    // 大于nums[i]的最小值
    it = set.upper_bound(nums[i]);
    if (it != set.end())
    {
      it++;
      if ((static_cast<long>(*it) - static_cast<long>(nums[i])) <= t)
        return true;
    }

    set.insert(nums[i]);

    // 范围控制
    if (i >= k)
    {
      set.erase(nums[i - k]);
    }
  }
  return false;
}
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
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/**
LCR 057. 存在重复元素 III
https://leetcode.cn/problems/7WqeDu/description/

给你一个整数数组 nums 和两个整数 k 和 t 。请你判断是否存在 两个不同下标 i 和 j，使得 abs(nums[i] - nums[j]) <= t ，同时又满足 abs(i - j) <= k 。
如果存在则返回 true，不存在返回 false。

示例 1：
输入：nums = [1,2,3,1], k = 3, t = 0
输出：true

示例 2：
输入：nums = [1,0,1,1], k = 1, t = 2
输出：true

示例 3：
输入：nums = [1,5,9,1,5,9], k = 2, t = 3
输出：false

提示：
0 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1
0 <= k <= 104
0 <= t <= 231 - 1
 */

// 代碼有问题，没通过
bool containsNearbyAlmostDuplicate1(vector<int> &nums, int k, int t)
{
  std::set<int> set;

  int count = nums.size();
  for (int i = 0; i < count; i++)
  {
    std::cout << " --- i:" << i << " ,num:" << nums[i] << std::endl;
    // 小于nums[i]的最大值
    // lower_bound 返回第一个 >= target 的元素
    auto it = set.lower_bound(nums[i]);
    if (it != set.begin())
    {
      it--;
      if ((static_cast<long>(nums[i]) - static_cast<long>(*it)) <= t)
      {
        std::cout << "lower_bound  *it:" << *it << std::endl;
        return true;
      }
    }

    // 大于nums[i]的最小值
    // upper_bound 返回第一个 > target 的元素
    it = set.upper_bound(nums[i]);
    if (it != set.end())
    {
      // it--;
      if ((static_cast<long>(*it) - static_cast<long>(nums[i])) <= t)
      {
        std::cout << "upper_bound  *it:" << *it << std::endl;
        return true;
      }
    }

    set.insert(nums[i]);

    // 范围控制
    if (i >= k)
    {
      set.erase(nums[i - k]);
    }
  }
  return false;
}

/**
 * 1、审题：
 * - 输入一个int数组，和两个整数k和t，判断在数组中寻找是否存在两个元素，下标分别是i和j，
 * - 要求下标的差值的绝对值小于k，且下标对应的元素差值的绝对值小于t
 * 2、解题：
 * - 1暴力解法：两层for循环，遍历元素i和j的值，判断是否存在满足要求的两个元素
 * - 使用TreeSet解法：由于要求i与j的差值要求小于等于k，则在遍历的时候只需要查找在范围[i-k,i+k]内判断是否存在值范围[nums[i]-t,num[i]+t]的元素
 * -- 可以使用TreeSet，问题转换为以nums[i]为基准的，小于nums[i]的最大值，和大于nums[i]的最小值，如果两种情况存在其一，则满足题目要求
 */
bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
{
  int count = nums.size();
  for (int i = 0; i < count; i++)
  {
    int j = i - k;
    for (; j <= i + k && j < count; j++)
    {
      if (j < 0 || j == i)
      {
        continue;
      }
      //   std::cout << "i:" << i << " ,j:" << j << std::endl;
      if (std::abs(static_cast<long>(nums[i]) - static_cast<long>(nums[j])) <= t)
      {
        // std::cout << "num[i]:" << nums[i] << " ,nums[j]:" << nums[j] << std::endl;
        return true;
      }
    }
  }
  return false;
}

int main()
{
  std::cout << "Hello, Algorithm!" << std::endl;

  TreeNode node1(1);
  TreeNode node2(2);
  TreeNode node3(3);
  TreeNode node4(4);
  TreeNode node5(5);
  TreeNode node6(6);
  TreeNode node7(7);

  node1.left = &node2;
  node1.right = &node3;

  node2.left = &node4;
  node2.right = &node5;

  node3.left = &node6;
  node3.right = &node7;

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
/**
 * 1、审题：
 * - 输入一个int数组，和两个整数k和t，判断在数组中寻找是否存在两个元素，下标分别是i和j，
 * - 要求下标的差值的绝对值小于k，且下标对应的元素差值的绝对值小于t
 * 2、解题：
 * - 1暴力解法：两层for循环，遍历元素i和j的值，判断是否存在满足要求的两个元素
 * - 使用TreeSet解法：由于要求i与j的差值要求小于等于k，则在遍历的时候只需要查找在范围[i-k,i+k]内判断是否存在值范围[nums[i]-t,num[i]+t]的元素
 * -- 可以使用TreeSet，问题转换为以nums[i]为基准的，小于nums[i]的最大值，和大于nums[i]的最小值，如果两种情况存在其一，则满足题目要求
 */
bool containsNearbyAlmostDuplicate1(vector<int> &nums, int k, int t)
{
  int count = nums.size();
  for (int i = 0; i < count; i++)
  {
    int j = i - k;
    for (; j <= i + k && j < count; j++)
    {
      if (j < 0 || j == i)
      {
        continue;
      }
      //   std::cout << "i:" << i << " ,j:" << j << std::endl;
      if (std::abs(static_cast<long>(nums[i]) - static_cast<long>(nums[j])) <= t)
      {
        // std::cout << "num[i]:" << nums[i] << " ,nums[j]:" << nums[j] << std::endl;
        return true;
      }
    }
  }
  return false;
}

int main()
{
  std::cout << "Hello, Algorithm!" << std::endl;

  TreeNode node1(1);
  TreeNode node2(2);
  TreeNode node3(3);
  TreeNode node4(4);
  TreeNode node5(5);
  TreeNode node6(6);
  TreeNode node7(7);

  node1.left = &node2;
  node1.right = &node3;

  node2.left = &node4;
  node2.right = &node5;

  node3.left = &node6;
  node3.right = &node7;

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